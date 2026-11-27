CC 				= gcc
AR 				= ar
CFLAGS 			= -Wall -Wextra -Werror -Wpedantic -MMD -MP $(INCLUDE_FLAGS)
INCLUDE_FLAGS 	= $(addprefix -I,$(INCLUDE_DIRS))
LDFLAGS 		= -Wl,-soname,$(LIB_SONAME)


SRC_DIR 		= src
TEST_DIR 		= test
INCLUDE_DIR 	= include
BUILD_DIR 		= build
INCLUDE_DIRS 	= $(INCLUDE_DIR) $(SRC_DIR) $(TEST_DIR)

INSTALL_DIR 	= /usr/local
INSTALL_INCDIR 	= $(INSTALL_DIR)/include
INSTALL_LIBDIR 	= $(INSTALL_DIR)/lib


SRCS 		= $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS 	= $(wildcard $(TEST_DIR)/*.c)
OBJS 		= $(patsubst $(SRC_DIR)/%.c, 	$(BUILD_DIR)/%.o, $(SRCS))
TEST_OBJS 	= $(patsubst $(TEST_DIR)/%.c, 	$(BUILD_DIR)/%.o, $(TEST_SRCS))
DEPS 		= $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)


LIB_NAME 			= libeh
LIB_MAJOR_VERSION 	= 1
LIB_MINOR_VERSION	= 0
LIB_PATCH_VERSION	= 0
LIB_SONAME 			= $(LIB_NAME).so.$(LIB_MAJOR_VERSION)
LIB_FULL 			= $(LIB_SONAME).$(LIB_MINOR_VERSION).$(LIB_PATCH_VERSION)


all: lib


-include $(DEPS) 


install: lib
	install -d $(INSTALL_INCDIR) $(INSTALL_LIBDIR)
	install -m 644 $(INCLUDE_DIR)/ehandler.h 	$(INSTALL_INCDIR)
	install -m 644 $(BUILD_DIR)/$(LIB_NAME).a	$(INSTALL_LIBDIR)
	install -m 644 $(BUILD_DIR)/$(LIB_FULL) 	$(INSTALL_LIBDIR)
	ln -sf $(LIB_FULL) 		$(INSTALL_LIBDIR)/$(LIB_SONAME)
	ln -sf $(LIB_SONAME) 	$(INSTALL_LIBDIR)/$(LIB_NAME).so


lib: CFLAGS += -O3
lib: $(OBJS) | $(BUILD_DIR)
	$(AR) cr $(BUILD_DIR)/$(LIB_NAME).a $^
	$(CC) -shared $(LDFLAGS) -o $(BUILD_DIR)/$(LIB_FULL) $^
	


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

uninstall:
	rm -rf $(INSTALL_INCDIR)/ehandler.h
	rm -rf $(INSTALL_LIBDIR)/$(LIB_NAME).a
	rm -rf $(INSTALL_LIBDIR)/$(LIB_NAME).so
	rm -rf $(INSTALL_LIBDIR)/$(LIB_SONAME)
	rm -rf $(INSTALL_LIBDIR)/$(LIB_FULL)
