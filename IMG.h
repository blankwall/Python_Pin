#ifndef A_H
#define A_H

// void add_hook(SPPY::PyObject*** hooks, SPPY::PyObject* new_hook);
//     SPPY::PyObject** hooks_list = *hooks;
//     if (hooks_list == NULL) {
//         hooks_list = (SPPY::PyObject**) malloc(sizeof(SPPY::PyObject*)*2);
//         hooks_list[0] = new_hook;
//         hooks_list[1] = NULL;
//     } else {
//         int hook_count;
//         for(hook_count=0; hooks_list[hook_count]; hook_count++);
//         hooks_list = (SPPY::PyObject**) realloc(hooks_list, sizeof(SPPY::PyObject*)*(hook_count+2));
//         hooks_list[hook_count] = new_hook;
//         hooks_list[hook_count+1] = NULL;
//     }

//     *hooks = hooks_list;
// }
// ------------------- auto generated
SPPY::PyObject* Python_IMG_Next(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_Prev(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_Invalid(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_Valid(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_SecHead(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_SecTail(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_RegsymHead(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_Entry(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_Name(SPPY::PyObject* self, SPPY::PyObject* args) ;
SPPY::PyObject* Python_IMG_Gp(SPPY::PyObject* self, SPPY::PyObject* args) ;
SPPY::PyObject* Python_IMG_LoadOffset(SPPY::PyObject* self, SPPY::PyObject* args) ;
SPPY::PyObject* Python_IMG_LowAddress(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_HighAddress(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_StartAddress(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_SizeMapped(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_Type(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_IsMainExecutable(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_IsStaticExecutable(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_Id(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_FindImgById(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_FindByAddress(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_AddInstrumentFunction(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_AddUnloadFunction(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_Open(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_IMG_Close(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_APP_ImgHead(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_APP_ImgTail(SPPY::PyObject* self, SPPY::PyObject* args);

#endif
