#include "image.h"

struct Gameimage gameimage;
imagelink* imagehead;
int hpwidth;
int hpheight;

void initimage() {
  loadimage(&gameimage.start, _T("image\\start.png"));

  loadimage(&gameimage.background1, _T("image\\background_0.png"));
  loadimage(&gameimage.background2[0], _T("image\\background_1_0.jpg"));
  loadimage(&gameimage.background2[1], _T("image\\background_1_1.jpg"));

  loadimage(&gameimage.img_role[0], _T("image\\role.jpg"));
  loadimage(&gameimage.img_role[1], _T("image\\role_red.jpg"));
  loadimage(&gameimage.img_role[2], _T("image\\role_blue.jpg"));

  loadimage(&gameimage.img_role_left[0], _T("image\\role_left.jpg"));
  loadimage(&gameimage.img_role_left[1], _T("image\\role_red_left.jpg"));
  loadimage(&gameimage.img_role_left[2], _T("image\\role_blue_left.jpg"));


  loadimage(&gameimage.bullet[0], _T("image\\bullet_0.jpg"));
  loadimage(&gameimage.bullet[1], _T("image\\bullet_1.jpg"));

  loadimage(&gameimage.bullet_left[0], _T("image\\bullet_left_0.jpg"));
  loadimage(&gameimage.bullet_left[1], _T("image\\bullet_left_1.jpg"));

  loadimage(&gameimage.hit[0], _T("image\\hit_0.jpg"));
  loadimage(&gameimage.hit[1], _T("image\\hit_1.jpg"));

  loadimage(&gameimage.fire[0], _T("image\\fire_0.jpg"));
  loadimage(&gameimage.fire[1], _T("image\\fire_1.jpg"));
  loadimage(&gameimage.fire_left[0], _T("image\\fire_0_left.jpg"));
  loadimage(&gameimage.fire_left[1], _T("image\\fire_1_left.jpg"));

  loadimage(&gameimage.role_panel, _T("image\\role_panel.png"));
  loadimage(&gameimage.hp, _T("image\\hp.png"));

  loadimage(&gameimage.winner[0], _T("image\\winner1.png"));
  loadimage(&gameimage.winner[1], _T("image\\winner2.png"));

  loadimage(&gameimage.backmenu, _T("image\\backmenu.png"));
}

void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //x为载入图片的X坐标，y为Y坐标
{

  // 变量初始化
  DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
  DWORD* draw = GetImageBuffer();
  DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
  int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
  int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
  int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
  int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
  int dstX = 0;    //在显存里像素的角标

  // 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
  for (int iy = 0; iy < picture_height; iy++)
  {
    for (int ix = 0; ix < picture_width; ix++)
    {
      int srcX = ix + iy * picture_width; //在显存里像素的角标
      int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
      int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
      int sg = ((src[srcX] & 0xff00) >> 8);   //G
      int sb = src[srcX] & 0xff;              //B
      if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
      {
        dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
        int dr = ((dst[dstX] & 0xff0000) >> 16);
        int dg = ((dst[dstX] & 0xff00) >> 8);
        int db = dst[dstX] & 0xff;
        draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
          | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
          | (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
      }
    }
  }
}

void initimagelinks() {
  imagehead = (imagelink*)malloc(sizeof(imagelink));
  if (imagehead == NULL) {
    exit(ERROR);
  }
  else {
    imagehead->next = NULL;
  }
}

void addimage(int x, int y, int endtime, IMAGE* image1, IMAGE* image2) {
  imagelink* newimage = (imagelink*)malloc(sizeof(imagelink));
  if (newimage == NULL) {
    exit(ERROR);
  }
  else {
    newimage->x = x;
    newimage->y = y;
    newimage->endtime = endtime;
    newimage->statrtime = clock();
    newimage->showimage1 = image1;
    newimage->showimage2 = image2;
    newimage->next = imagehead->next;
    imagehead->next = newimage;
    return;
  }
  
}

void updataimage() {
  imagelink* p = imagehead;
  imagelink* deletep;
  while (p->next != NULL) {
    putimage(p->next->x, p->next->y, p->next->showimage1, SRCAND);
    putimage(p->next->x, p->next->y, p->next->showimage2, SRCINVERT);
    if (clock() - (p->next->statrtime) > p->next->endtime) {
      deletep = p->next;
      p->next = deletep->next;
      free(deletep);
      continue;
    }
    p = p->next;
  }
}