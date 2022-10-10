/*   Monitoring   */

// tl3ly el bit rate

enum status  { Idle , Sending , Receiving };
int bytes;     // length of frame sent
int frames;    // number of frames sent

int getBytes()
{
    return bytes;
}
void setBytes(int b)
{
    bytes = b;
}
int getFrames()
{
    return frames;
}
void setFrames(int f)
{
    frames = f;
}
status getStatus()
{
    return status;
}
void setStatus(status s)
{
    status = s;
}
