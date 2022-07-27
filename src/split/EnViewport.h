#ifndef __EN_3D_VIEWPORT__
#define __EN_3D_VIEWPORT__

#include <Editor.h>

typedef struct {
	ViewContext view;
	SkelAnime   skelAnime;
	s8 headerClick;
} EnViewport;

extern SplitTask gEnViewportTask;

#endif