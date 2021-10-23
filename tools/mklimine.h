#include <stdint.h>
#include <stddef.h>
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32; typedef uint64_t u64; typedef int8_t i8;
typedef size_t usiz; typedef uintptr_t uptr; 

#pragma pack(push,1)

typedef struct both16 { u16 native; u16 foreign; } both16;
typedef struct both32 { u32 native; u32 foreign; } both32;
static inline both16 b16(u16 val) { return (both16) { .native = val, .foreign = __builtin_bswap16(val) }; }
static inline both32 b32(u32 val) { return (both32) { .native = val, .foreign = __builtin_bswap32(val) }; }

typedef struct pvd_datetime {
    char year[4], month[2], day[2], hour[2], min[2], sec[2], centisec[2];
    i8 timezoneoff; // 15 minute intervals from GMT
} pvd_datetime;

typedef struct dir_datetime {
    u8 year, month, day, hour, min, sec;
    i8 timezoneoff; // 15 minute intervals from GMT
} dir_datetime;


typedef enum { ent_normal = 0, ent_hidden = 1 << 0 } ent_flags;

typedef struct susp_entry {
    char sig[2];
    u8 len_sue, ver;
    u8 data[];
} susp_entry;

typedef struct dir_record {
	u8 len, extlen;
	both32 extent_lba, data_len;
	dir_datetime recinfo;
	u8 flags, interl_size, interl_gap;
	both16 volume_seq;
	u8 fname_len;
} dir_record;

const usiz DIR_SIZE = sizeof(dir_record) + 1; // dot and dotdot
const usiz DIR_ENT30_SIZE = sizeof(dir_record) + 30 + 2 + sizeof(susp_entry) + 1 + 30; // 30 characters max, Rock Ridge

typedef enum used_sectors { lba_pvd = 16, lba_bootrec, lba_terminator, lba_bcat, lba__, lba_free } used_sectors;

typedef struct vol_desc {
	u8 code; char ident[5]; u8 ver;
	union {
        struct { char bootsystem[32], boot[32]; u32 bootcatalog_lba; }; // boot record
        struct { // pvd
            u8 _0; char system_ident[32], vol_ident[32]; u8 _1[8];
            both32 vol_space_siz; u8 _2[32];
            both16 vol_set_size, vol_seq_no, logic_blk_siz;
            both32 path_tab_siz; both16 le_path_tab_lba, le_opt_path_tab_lba, be_path_tab_lba, be_opt_path_tab_lba;
            dir_record root; char root_name;
            char vol_set_ident[128], publisher_ident[128], data_prep_ident[128], app_filename[128], copyright_filename[37], abstract_filename[37], biblio_filename[37];
            pvd_datetime creat, mod, expiration, effective;
            u8 ver2, _4;
        };
    };
} vol_desc;


typedef enum { elt_x86 = 0x00, elt_efi = 0xEF } elt_platforms;

typedef struct section_entry {
	u8 boot_indicator, boot_media;
	u16 segment;
	u8 sys_type, _0;
	u16 sec_count; // important: 512-byte sectors
	u32 load_rba; // 2048-byte lba limine-eltorito-efi
	u8 _1[20];
} section_entry;

typedef enum type_code {
	typecode_bootrecord = 0, typecode_primary, typecode_supplementary, typecode_volume_part, typecode_terminator = 255,
} type_code;

typedef union boot_catalog {
    u8 indicator;
    struct { // indicator == 1
        u8 indicator, platf_id;
        u16 _0;
        char manuf_id[24];
        u16 checksum, id55AA;
    } catalog;
    section_entry boot;
    struct { // 0x90 (more follow), 0x91 (end of chain)
        u8 indicator, platf_id;
        u16 entries;
        u8 id[28];
    } section;
} boot_catalog;

typedef struct mbr_ptab {
    u8 drive_attr, chs[3], ptype, chs_last[3];
    u32 part_lba, sectors;
} mbr_ptab;

typedef struct mbr {
    u8 _0[440-2*2-8*2];
    u16 size_a, size_b;
    u64 loc_a, loc_b;
    u32 diskid;
    u8 _1[2];
    mbr_ptab part[4];
    u8 _2[2];
} mbr;

typedef struct gpt {
    char signature[8];
    u32 revision, hdrsiz, hdrcrc, _0;
    u64 hdrlba, althdrlba;
    u64 first_usable, last_usable;
    u8 guid[16];
    u64 gpt_ents_lba;
    u32 part_ents, size_ent, gpt_ents_crc;
} gpt;

typedef struct gpt_ent {
    u8 type_guid[16], part_guid[16];
    u64 first_lba, last_lba, attr;
    u16 part_name[36];
} gpt_ent;

// EFI System Partition: C12A7328-F81F-11D2-BA4B-00A0C93EC93B
const u8 esp_guid[16] = {0x28, 0x73, 0x2A, 0xC1, 0x1F, 0xF8, 0xD2, 0x11, 0xBA, 0x4B, 0x00, 0xA0, 0xC9, 0x3E, 0xC9, 0x3B };

typedef enum { idx_efi = 0, idx_sys, idx_cd, idx_hdd } sys_files;
static inline usiz sec_roundup(usiz len) { return (len + 2047) / 2048; }

static inline u32 crc32(const void *data, usiz siz) {
    const u8 *stream = (const u8*)data;
    u32 crc = 0xffffffff;
    static u32 table[0x100];
    if (!*table) for (usiz i = 0; i < 256; i++) {
        u32 c = i;
        for (usiz j = 0; j < 8; j++) c = (c >> 1) ^ ((c & 1) ? 0xEDB88320 : 0);
        table[i] = c;
    }

    for (usiz i = 0; i < siz; i++) crc = (crc >> 8) ^ table[(crc ^ stream[i]) & 0xff];
    return ~crc;
}
#pragma pack(pop)
