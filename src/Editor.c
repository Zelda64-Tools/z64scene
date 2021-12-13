#include "Editor.h"
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>

const char* sBuild = {
	"z64scene alpha commit[ "
	#ifndef __COMFLAG__
	GIT_COMMIT_MSG
	#endif
	" ]"
};

const char* sHash = {
	""
	#ifndef __COMFLAG__
	GIT_COMMIT_HASH
	#endif
};

static f64 prevTime;
static f64 curTime;

/* / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / */

void Editor_Draw(EditorContext* editorCtx) {
	if (glfwGetWindowAttrib(editorCtx->appInfo.mainWindow, GLFW_ICONIFIED))
		return;
	
	Gui_Draw(editorCtx);
}

void Editor_Update_FramerateLimit(EditorContext* editorCtx) {
	if (editorCtx->frameRate > 1.0) {
		while (curTime - prevTime < 1.0 / editorCtx->frameRate ) {
			curTime = glfwGetTime();
		}
		prevTime = curTime;
	} else {
		prevTime = glfwGetTime();
	}
}

void Editor_Update(EditorContext* editorCtx) {
	if (glfwGetWindowAttrib(editorCtx->appInfo.mainWindow, GLFW_ICONIFIED))
		return;
	
	Gui_Update(editorCtx);
	Cursor_Update(&editorCtx->cursorCtx);
	Editor_Update_FramerateLimit(editorCtx);
}

void Editor_Init(EditorContext* editorCtx) {
	GuiContext* regionCtx = &editorCtx->guiCtx;
	
	editorCtx->frameRate = 60.0f;
	
	#ifndef NDEBUG
	editorCtx->vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
	#else
	editorCtx->vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
	#endif
	if (editorCtx->vg == NULL)
		printf_error("Could not init nanovg.");
	editorCtx->fontCtx.notoSansID = nvgCreateFont(editorCtx->vg, "sans", "Menlo-Regular.ttf");
	if (editorCtx->fontCtx.notoSansID < 0) {
		OsPrintfEx("Could not load Font");
	}
	
	editorCtx->viewCtx.cameraControl = false;
	Gui_Init(editorCtx);
	Cursor_Init(&editorCtx->cursorCtx);
	
	for (s32 i = -4; i < 22; i++) {
		s32 o = Lib_Wrap(i, -8, 11);
		OsPrintf("%d - %d", i, o);
	}
	
	glfwSetWindowSizeLimits(
		editorCtx->appInfo.mainWindow,
		400,
		200,
		GLFW_DONT_CARE,
		GLFW_DONT_CARE
	);
}