
unsigned char seven_seg[]= {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void display()
{	
	if(cp==0){P2=~0x40;P3=seven_seg[show/1000];}
	if(cp==1){P2=~0x20;P3=seven_seg[show/100%10] & ~0x80;}
	if(cp==2){P2=~0x10;P3=seven_seg[show/10%10];}
	if(cp==3){P2=~0x08;P3=seven_seg[show%10];}
}