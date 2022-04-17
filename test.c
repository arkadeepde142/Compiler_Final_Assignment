union node
{
    int x, y, z;
} temp, temp1;
void main()
{
    union node t;
    int a = temp.x + temp1.y;
}