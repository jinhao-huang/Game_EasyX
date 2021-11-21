#include "image.h"

struct Gameimage gameimage;
imagelink* imagehead;

void initimagelinks() {
  imagehead = (imagelink*)malloc(sizeof(imagelink));
  imagehead->next = NULL;
}

void addimage(int x, int y, int endtime, IMAGE* image1, IMAGE* image2) {
  imagelink* newimage = (imagelink*)malloc(sizeof(imagelink));
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