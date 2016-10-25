width = 16
height = 16
bitmap = [0x01, 0x01, 0x33, 0xFD, 0x4B, 0xCD, 0x48, 0xFC, 
  0xB6, 0x01, 0x85, 0x31, 0x86, 0x78, 0x00, 0x00, 
  0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x00, 0x00, 
0x01, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00]

'''[ 0xC0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFE, 0xFA, 0xE4, 0xC8, 0x30, 0xC0, 
  0x03, 0x0F, 0x13, 0x27, 0x4F, 0x55, 0x8B, 0xBF, 
  0xBF, 0xBF, 0x7B, 0x7F, 0x3F, 0x1F, 0x0E, 0x03]
'''

#[0x1C, 0x22, 0x6A, 0xC1, 0x65, 0x65, 0xC1, 0x6A, 
#  0x22, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#  0x3F, 0x0A, 0x05, 0x07, 0x0C, 0x0C, 0x07, 0x05, 
#0x0A, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]

#[0xFC, 0x78, 0x3E, 0xFC, 0x1E, 0xFE, 0x0F, 0xD6, 
#0x1F, 0xEF, 0x38, 0xEF, 0x38, 0xEF, 0x1F, 0xEF, 
#0x0F, 0xD6, 0x1C, 0xFE, 0x3E, 0x7C, 0xFE, 0x7C, 
#0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]


strbuffer = ''

bitbuffer = []

rowbuf = ['','','','','','','','','','','','','','','','']

#byteWidth = (width + 7) / 8
w = 0
h = 0
for b in bitmap:
    for a in [2**x for x in range(7,-1,-1)]:
        if (a & b) == 0:
            strbuffer+='0'
            rowbuf[w]+='0'
            bitbuffer.append(0);
        else:
            strbuffer+='1'
            rowbuf[w]+='1'
            bitbuffer.append(1);
        w+=1
        if w == width:
            w = 0
            h+=1
            strbuffer+='\n'
print strbuffer
print 'or...'
print 'bits:'
print bitbuffer

rowbuf = ['','','','','','','','','','','','','','','','']
bytebuf = ['','','','','','','','','','','','','','','','']
#Reverse order WHY
row = height-8
for i in range(len(bitbuffer)/8):
    for j in range(8):
        rowbuf[row+j]+='%d'%bitbuffer[i*8+j]
    if i == 15:#i % (width-1) == 0:
        row-=8

for r in rowbuf:
    print r        
#for offset in range(16):
#    strbuffer = ''
    

'''
for r in rowbuf:
    print r
print 'or...'

buffer = [[0]*16]*16

byteWidth = (w + 7) / 8;
for yi in range(0,height):
    for xi in range(0,width):
        if (bitmap[yi * byteWidth + xi / 8] & (128 >> (xi & 7)) ) != 0:
            #if bitmap[
            buffer[xi][yi] = 1

for i in range(len(buffer)):
    buf = ''
    for j in range(len(buffer[0])):
        buf+='%d'%buffer[i][j]
    print buf
'''    

'''
WIDTH=16
buffer = range(0,16*16)

yOffset = 0
sRow = 0;
rows = height/8;
if height%8!=0:
    rows+=1;
for a in range(0,rows):
    bRow = sRow + a;
    if bRow > -2:
      for iCol in range(0,w):
        if iCol >= 0:
          if bRow >= 0:
            buffer[ (bRow*WIDTH) + iCol ] = bitmap[(a*w)+iCol] << yOffset;
          if (yOffset && bRow<(HEIGHT/8)-1 && bRow > -2) {
            if      (color == WHITE) this->sBuffer[ ((bRow+1)*WIDTH) + x + iCol ] |= pgm_read_byte(bitmap+(a*w)+iCol) >> (8-yOffset);
            else if (color == BLACK) this->sBuffer[ ((bRow+1)*WIDTH) + x + iCol ] &= ~(pgm_read_byte(bitmap+(a*w)+iCol) >> (8-yOffset));
            else                     this->sBuffer[ ((bRow+1)*WIDTH) + x + iCol ] ^= pgm_read_byte(bitmap+(a*w)+iCol) >> (8-yOffset);
          }
        }
      }
    }
  }'''