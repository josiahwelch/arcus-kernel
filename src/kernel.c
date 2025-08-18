void main() {
    char* video_memory = (char*)0xB8000;
    *video_memory++ = 'A';
    *video_memory++ = 'r';
    *video_memory++ = 'c';
    *video_memory++ = 'a';
    *video_memory++ = ' ';
    *video_memory++ = 'k';
    *video_memory++ = 'e';
    *video_memory++ = 'r';
    *video_memory++ = 'n';
    *video_memory++ = 'e';
    *video_memory++ = 'l';
}
