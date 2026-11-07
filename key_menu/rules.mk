SRC += menu.c
USE_DEFAULT_MENU ?= yes
ifeq (yes, $(strip $(USE_DEFAULT_MENU)))
	SRC += default_menu.c
endif
REPEAT_KEY_ENABLE = yes # so that record has a keycode field
