// All three commands execute within onOpen, before another menu or input frame.
// Restoring after setu also marks the newly registered userinfo field as changed.
#define OPENCJ_REGISTER_FPS(RUN) \
    RUN "setfromdvar opencj_fps_saved com_maxfps"; \
    RUN "setu com_maxfps 999"; \
    RUN "setfromdvar com_maxfps opencj_fps_saved";
