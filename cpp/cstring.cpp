static int strstr_count(const unsigned char *src, const unsigned char *cmp)
{
    int count = 0 , i = 0,j;
    while(src[i] != '\0')
    {
            j = 0;
            while(src[i+j] == cmp[j] && cmp[j]!='\0')
                    ++j;
            if(cmp[j]=='\0')
                    ++count;
            ++i;
    }
    return count;
}
static int strstr_pos(const unsigned char *src, const unsigned char *cmp, int index)
{
    int count = 0 , i = 0,j;
    while(src[i] != '\0')
    {
            j = 0;
            while(src[i+j] == cmp[j] && cmp[j]!='\0')
                    ++j;
            if(cmp[j]=='\0')
                    ++count;
            ++i;
            if(count == index){
                break;
            }
    }
    if(count < index){
        return -1;
    }
    return i;
}
