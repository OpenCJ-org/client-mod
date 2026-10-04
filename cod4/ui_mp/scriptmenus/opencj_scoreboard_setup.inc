// Shared by standalone scoreboard setup and the connection initializer.
#define OPENCJ_SETUP_SCOREBOARD(RUN) \
    setDvar opencj_sb_up "set opencj_sb_held 0; setu opencj_sb_active 0; bind TAB vstr opencj_sb_down"; \
    setDvar opencj_sb_down "set opencj_sb_held 1; setu opencj_sb_active 1; bind TAB \\\"+scores; vstr opencj_sb_up; set opencj_sb_release\\\""; \
    RUN "set opencj_sb_held 0"; \
    RUN "setu opencj_sb_active 0"; \
    RUN "bind TAB vstr opencj_sb_down"; \
    RUN "setu opencj_sb_ready 3";
