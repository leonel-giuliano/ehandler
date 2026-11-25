CC 				= gcc
AR 				= ar
CFLAGS 			= -Wall -Wextra -Werror -pedantic -MMD -MP -I $(INCLUDE_DIR)
SHARED_FLAGS	= -Wl,-soname,$(LIB_VERSION)


SRC_DIR 	= src
TEST_DIR 	= test
INCLUDE_DIR = include
BUILD_DIR 	= build

INSTALL_DIR 	= /usr/local
INSTALL_LIBDIR 	= $(INSTALL_DIR)/lib
INSTALL_INCDIR 	= $(INSTALL_DIR)/include


SRCS 		= $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS 	= $(wildcard $(TEST_DIR)/*.c)
OBJS 		= $(patsubst $(SRC_DIR)/%.c, 	$(BUILD_DIR)/%.o, $(SRCS))
TEST_OBJS 	= $(patsubst $(TEST_DIR)/%.c, 	$(BUILD_DIR)/%.o, $(TEST_SRCS))
DEPS 		= $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)


LIB_NAME 			= libeh
LIB_MAJOR_VERSION 	= 1
LIB_MINOR_VERSION 	= 0
LIB_PATCH_VERSION 	= 0
LIB_VERSION 		= $(LIB_NAME).so.$(LIB_MAJOR_VERSION)
LIB_FULL_VERSION 	= $(LIB_VERSION).$(LIB_MINOR_VERSION).$(LIB_PATCH_VERSION)


all: lib


-include $(DEPS)


install: all
	install -d $(INSTALL_LIBDIR) $(INSTALL_INCDIR)
	install -m 644 $(BUILD_DIR)/$(LIB_FULL_VERSION) $(INSTALL_LIBDIR)
	ln -sf $(LIB_FULL_VERSION) $(INSTALL_LIBDIR)/$(LIB_VERSION)
	ln -sf $(LIB_VERSION) $(INSTALL_LIBDIR)/$(LIB_NAME).so
	install -m 644 $(BUILD_DIR)/$(LIB_NAME).a $(INSTALL_LIBDIR)
	install -m 644 $(INCLUDE_DIR)/ehandler.h $(INSTALL_INCDIR)


lib: $(OBJS) | $(BUILD_DIR)
	$(AR) cr $(BUILD_DIR)/$(LIB_NAME).a $^
	$(CC) -o $(BUILD_DIR)/$(LIB_FULL_VERSION) $^ -shared $(SHARED_FLAGS)


test: CFLAGS += -g -O0 -DLIBEH_DEBUG
test: $(OBJS) $(TEST_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -fpic -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@


clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(INSTALL_LIBDIR)/$(LIB_FULL_VERSION)
	rm -rf $(INSTALL_LIBDIR)/$(LIB_VERSION)
	rm -rf $(INSTALL_LIBDIR)/$(LIB_NAME).so
	rm -rf $(INSTALL_LIBDIR)/$(LIB_NAME).a
	rm -rf $(INSTALL_INCDIR)/ehandler.h
