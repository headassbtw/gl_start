#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define LINUX

#ifdef WINDOWS
#define FILEPATH_DELIMITER "\"
#endif
#ifdef LINUX
#define FILEPATH_DELIMITER "/"
#endif