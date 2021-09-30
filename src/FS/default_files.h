void createNativeFiles()
{
 createFile("hello");
 writeFile("hello", "movn af 6\ncmdn 4 1\nmovn ac 'H\ncmdn 1 1\nmovn ac 'e\ncmdn 1 1\nmovn ac 'l\ncmdn 1 1\nmovn ac 'l\ncmdn 1 1\nmovn ac 'o\ncmdn 1 1\nmovn ac ',\ncmdn 1 1\nmovn ac 'M\ncmdn 1 1\nmovn ac 'e\ncmdn 1 1\nmovn ac 'x\ncmdn 1 1\n");
 createFile("build.sh");
 writeFile("build.sh", "echo building...\nmex hello\nrename out.mex hello.mex\nmex ascii\nrename out.mex ascii.mex\necho done\n");
 createFile("ascii");
 writeFile("ascii", "movn ac 127\naddn ac 127\ncmdn 1 1\nsubn ac 1\nbign ac 1\njnzn 8 1\n");
}