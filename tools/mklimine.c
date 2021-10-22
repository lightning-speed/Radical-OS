#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mklimine.h"

// string functions
#define PTR_LEN(str) str, sizeof(str)
usiz delim_len(const char *str, const char terminator) {
	usiz len = 0;
	while (str[len] != terminator) len++;
	return len;
}
const char *append(const char *prefix, const char *suffix, usiz slen) {
    static char buffer[FILENAME_MAX];
    if (prefix == NULL) {
        memcpy(buffer, suffix, slen);
        buffer[slen] = 0;
        return buffer;
    }
    usiz plen = strlen(prefix);
    if ((plen + slen + 1) > FILENAME_MAX) {
        fprintf(stderr, "Path too big");
        exit(EXIT_FAILURE);
    }
    memcpy(buffer, prefix, plen);
    buffer[plen] = '/';
    memcpy(buffer + plen + 1, suffix, slen);
    buffer[plen + 1 + slen] = 0;
    return buffer;
}

// construct iso9660 image
void date(pvd_datetime *pvd_date, dir_datetime *dir_date) {
    if (pvd_date != NULL) {
        memcpy(pvd_date->centisec, "00", 2); memcpy(pvd_date->sec, "00", 2);
        memcpy(pvd_date->min, "00", 2); memcpy(pvd_date->hour, "00", 2);
        memcpy(pvd_date->day, "01", 2); memcpy(pvd_date->month, "01", 2); memcpy(pvd_date->year, "1970", 4);
    }
    if (dir_date != NULL) {
        pvd_date->timezoneoff = 0;
        *dir_date = (dir_datetime) { .year = 7, .month = 1, .day = 1, .hour = 0, .min = 0, .sec = 0, .timezoneoff = 0 };
    }
}
void init_pvd(u8 *iso, usiz pvd_sector, usiz vol_size, u32 rootlba, u32 root_secs) {
    pvd_datetime pvd_date; dir_datetime dir_date; date(&pvd_date, &dir_date);
    
    vol_desc *pvd = (void*)(iso + pvd_sector * 2048);
    *pvd = (vol_desc) { .code = typecode_primary, .logic_blk_siz = b16(2048), .vol_space_siz = b32(vol_size / 2048), .vol_set_size = b16(1), .vol_seq_no = b16(1), .ver = 1, .ver2 = 1, .creat = pvd_date, .mod = pvd_date };
    memcpy(pvd->ident, "CD001", 5);
    memset(pvd->system_ident, ' ', 32); 
    memset(pvd->vol_ident, ' ', 32); strcpy(pvd->vol_ident, "MKLIMINE");
    memset(pvd->vol_set_ident, ' ', 128); memset(pvd->publisher_ident, ' ', 128);
    memset(pvd->data_prep_ident, ' ', 128); strcpy(pvd->data_prep_ident, "MKLIMINE");
    memset(pvd->app_filename, ' ', 128); memset(pvd->copyright_filename, ' ', 37); memset(pvd->abstract_filename, ' ', 37); memset(pvd->biblio_filename, ' ', 37);
    
    pvd->root = (dir_record) { .extent_lba = b32(rootlba), .data_len = b32(root_secs * 2048), .len = 34, .flags = 2, .volume_seq = b16(1), .fname_len = 1, .recinfo = dir_date };
}
void init_bootrec(u8 *iso, usiz bootrec_sec, usiz elt_bcat_sec) {
    vol_desc *bootrec = (void*)(iso + bootrec_sec * 2048);
    *bootrec = (vol_desc) { .code = typecode_bootrecord, .ver = 1, .bootcatalog_lba = elt_bcat_sec };
    memcpy(bootrec->ident, "CD001", 5);
    strcpy(bootrec->bootsystem, "EL TORITO SPECIFICATION");
}
void init_terminator(u8 *iso, usiz term_sec) {
    vol_desc *terminator = (void*)(iso + term_sec * 2048);
    terminator->code = typecode_terminator;
    memcpy(terminator->ident, "CD001", 5);
}
void init_bcat(u8 *iso, usiz bcat_sec, usiz bioscd_sec, usiz bioscd_len, usiz efi_sec, usiz efi_secs, usiz pvd_sec) {
    u32 *elt_img_info = (void *)(iso + bioscd_sec * 2048 + 8);
    elt_img_info[0] = pvd_sec;
    elt_img_info[1] = bioscd_sec;
    elt_img_info[2] = bioscd_len; // TODO: add checksum

    boot_catalog *bcat = (void*)(iso + bcat_sec * 2048);
    bcat->indicator = 1;
    bcat->catalog.platf_id = elt_x86; memset(bcat->catalog.manuf_id, 0, 24); bcat->catalog.checksum = 0x55AA; bcat->catalog.id55AA = 0xAA55;
    
    bcat = (void*)((uptr)bcat + sizeof(bcat->catalog));
    bcat->indicator = 0x88;
    bcat->boot.boot_media = 0; bcat->boot.segment = 0; bcat->boot.sys_type = 0;
    bcat->boot.sec_count = 4; bcat->boot.load_rba = bioscd_sec; // 2048 bytes is the only val supported by tons of old BIOSes

    bcat = (void*)((uptr)bcat + sizeof(bcat->boot));
    bcat->indicator = 0x91; bcat->section.platf_id = elt_efi; bcat->section.entries = 1; memset(bcat->section.id, 0, 28);
    section_entry *ent = (void*)((uptr)bcat + sizeof(bcat->section));
    ent->boot_indicator = 0x88; ent->boot_media = 0; ent->segment = 0; ent->sys_type = 0;
    ent->sec_count = efi_secs; ent->load_rba = efi_sec;
}

usiz init_dir(u8 *iso, usiz dirs_sec, usiz dir_secs, dir_record *parent) {
    pvd_datetime pvd_date; dir_datetime dir_date; date(&pvd_date, &dir_date);
    
    u32 parent_sec = parent ? parent[0].extent_lba.native : dirs_sec, parent_secs = parent ? parent[0].data_len.native / 2048 : dir_secs;
    dir_record *dirs = (void*)(iso + dirs_sec * 2048);

    *dirs = (dir_record) { .len = sizeof(dir_record) + 1, .extent_lba = b32(dirs_sec), .data_len = b32(dir_secs * 2048), .flags = 2, .volume_seq = b16(1), .fname_len = 1, .recinfo = dir_date }; 
    ((u8 *)dirs + sizeof(dir_record))[0] = 0;
    dirs = (void*)((uptr)dirs + dirs->len);

    *dirs = (dir_record) { .len = sizeof(dir_record) + 1, .extent_lba = b32(parent_sec), .data_len = b32(parent_secs * 2048), .flags = 2, .volume_seq = b16(1), .fname_len = 1, .recinfo = dir_date }; 
    ((u8 *)dirs + sizeof(dir_record))[0] = 1;
    dirs = (void*)((uptr)dirs + dirs->len);

    return dirs_sec * 2048 + (sizeof(dir_record) + 1) * 2;
}

void dir_entry(u8 *iso, usiz *dir_offset, const char *name, u32 data_lba, u32 data_secs, ent_flags flags) {
    pvd_datetime pvd_date; dir_datetime dir_date; date(&pvd_date, &dir_date);
    u8 name_len = strlen(name), nameent_len = name_len + 2, padding = (sizeof(dir_record) + name_len) ? 1 : 0, rrip_len = sizeof(susp_entry) + 1 + name_len;
    u8 total_len = sizeof(dir_record) + nameent_len + padding + rrip_len;
    if (sec_roundup(*dir_offset) != sec_roundup(*dir_offset + total_len)) *dir_offset = sec_roundup(*dir_offset);
    dir_record *dir = (void*)(iso + *dir_offset);

    *dir = (dir_record) { .flags = flags, .len = total_len, .extent_lba = b32(data_lba), .data_len = b32(data_secs), .volume_seq = b16(1), .fname_len = nameent_len, .recinfo = dir_date };
    u8 *data = (u8 *)dir + sizeof(dir_record);
    memcpy(data, name, name_len);
    memcpy(data + nameent_len, ";1", 2);
    susp_entry *e = (void*)(data + nameent_len + padding);
    memcpy(e->sig, "NM", 2);
    e->len_sue = rrip_len; e->ver = 1;
    e->data[0] = 0; // flags
    memcpy(e->data + 1, name, name_len);
    *dir_offset += total_len;
}

// isohybrid
void init_mbr(u8 *iso, usiz size, usiz cd_start, usiz cd_len) {
    usiz s2_size = cd_len - 2048, s2_sects = (s2_size + 511) / 512;
    mbr *bootrec = (void*)iso;
    bootrec->size_a = (s2_sects / 2) * 512 + (s2_sects % 2 ? 512 : 0);
    bootrec->size_b = (s2_sects / 2) * 512;
    bootrec->loc_a = ((cd_start + 1) * 2048);
    bootrec->loc_b = bootrec->loc_a + bootrec->size_a;
    bootrec->part[0] = (mbr_ptab) { .drive_attr = 0, .ptype = 0xEE, .part_lba = 1, .sectors = (size + 511) / 512 };
}
void init_gpt(u8 *iso, usiz efi_start, usiz efi_len) {
    usiz efi_start_lba = efi_start * 4, efi_end_lba = efi_start_lba + (efi_len + 511) / 512 - 1; // end is inclusive
    gpt *hdr = (void*)(iso + 512);
    *hdr = (gpt) {
        .revision = 65536, .hdrsiz = sizeof(gpt), .hdrlba = 1,
        .first_usable = efi_start_lba, .last_usable = efi_end_lba,
        .gpt_ents_lba = 2, .part_ents = 1, .size_ent = sizeof(gpt_ent)
    };
    memcpy(hdr->signature, "EFI PART", 8);

    gpt_ent *ents = (void*)(iso + 512 * 2);
    ents[0].first_lba = efi_start_lba;
    ents[0].last_lba = efi_end_lba;
    memcpy(ents[0].part_guid, esp_guid, 16);
   
    hdr->gpt_ents_crc = crc32(ents, hdr->size_ent);
    hdr->hdrcrc = crc32(hdr, hdr->hdrsiz);
}

// file reading
typedef struct file_info {
    FILE *fp;
    usiz start_lba, size;
    const char *dir, *name; usiz namelen;
    const char *isoname;
} file_info;
void finfo2(file_info *out, const char *dir, const char *name, usiz namelen, const char *isoname, usiz start_lba, usiz size) {
    *out = (file_info) { .dir = dir, .name = name, .namelen = namelen, .size = size, .start_lba = start_lba, .isoname = isoname };
    const char *n = append(dir, name, namelen);
    out->fp = fopen(n, "rb");
    if (out->fp == NULL) {
        fprintf(stderr, "File open error. Check that %s is accessible\n", n);
        exit(EXIT_FAILURE);
    }
}
void finfo(file_info *out, const char *dir, const char *name, usiz namelen, const char *isoname, usiz *cur_lba) {
    finfo2(out, dir, name, namelen, isoname, *cur_lba, 0);
    if (fseek(out->fp, 0, SEEK_END) != 0) {
        fprintf(stderr, "Error while calculating the file size\n");
        exit(EXIT_FAILURE);
    }
    out->size = ftell(out->fp);
    rewind(out->fp);
    *cur_lba += sec_roundup(out->size);
}

// main
void usage() {
    fprintf(stderr,
        "mklimine: isohybrid image creator.\n"
        "Usage: mklimine [output iso] [limine binary dir] [FS path:ISO path]...\n"
        "Example: mklimine myos.iso build/limine-bin src/limine.cfg:limine.cfg build/kernel.elf:kernel.elf\n");
    exit(EXIT_FAILURE);
}

const int ROUNDING = 8 * 4096;
int main(const int argc, const char **argv) {
    if (argc <= 2) usage();
    const char *output = argv[1], *dir = argv[2];
    usiz user_files = argc - 3, sys_files = 4;
    usiz files = user_files + sys_files;
    file_info *info = malloc(files * sizeof(file_info));
    if (!info) { fprintf(stderr, "Allocation error\n"); exit(EXIT_FAILURE); }
    
    usiz cur = lba_free;
    finfo(info + idx_efi, dir, PTR_LEN("limine-eltorito-efi.bin"), NULL, &cur);
    finfo(info + idx_sys, dir, PTR_LEN("limine.sys"), "limine.sys", &cur);
    finfo(info + idx_cd, dir, PTR_LEN("limine-cd.bin"), NULL, &cur);    
    finfo2(info + idx_hdd, dir, PTR_LEN("limine-hdd.bin"), NULL, 0, 512);

    for (usiz i = 0; i < user_files; i++) {
        const char *str = argv[3 + i];
        usiz len = delim_len(str, ':');
        finfo(info + sys_files + i, NULL, str, len, str + len + 1, &cur);
    }

    usiz dirs_sec = cur, dirs_size = 0;
    dirs_size += DIR_SIZE;
    dirs_size += DIR_ENT30_SIZE * (user_files + 1); // add limine.sys
    cur += sec_roundup(dirs_size);
    
    usiz size = cur * 2048;
    size += ((size % ROUNDING) != 0) ? ROUNDING - (size % ROUNDING) : 0;

    u8 *iso = calloc(size, 1);
    if (!iso) { fprintf(stderr, "Allocation error\n"); exit(EXIT_FAILURE); }

    usiz root_off = init_dir(iso, dirs_sec, sec_roundup(dirs_size), NULL);
    for (usiz i = 0; i < files; i++) {
        file_info in = info[i]; 
        if (fread(iso + in.start_lba * 2048, in.size, 1, in.fp) != 1) {
            fprintf(stderr, "Read error\n"); exit(EXIT_FAILURE);
        }
        fclose(in.fp);
        if (in.isoname != NULL) dir_entry(iso, &root_off, in.isoname, in.start_lba, in.size, (i == idx_sys) ? ent_hidden : 0);
    }

    init_mbr(iso, size, info[idx_cd].start_lba, info[idx_cd].size);
    init_gpt(iso, info[idx_efi].start_lba, info[idx_efi].size);
    init_pvd(iso, lba_pvd, size, dirs_sec, sec_roundup(dirs_size));
    init_bootrec(iso, lba_bootrec, lba_bcat);
    init_terminator(iso, lba_terminator);
    init_bcat(iso, lba_bcat, info[idx_cd].start_lba, info[idx_cd].size, info[idx_efi].start_lba, (info[idx_efi].size + 511) / 512, lba_pvd);

    FILE *isofile = fopen(output, "wb");
    if (isofile == NULL) { fprintf(stderr, "Can't open output file\n"); exit(EXIT_FAILURE); }
    if (fwrite(iso, size, 1, isofile) != 1) { fprintf(stderr, "Error while writing the ISO\n"); exit(EXIT_FAILURE); }
}
