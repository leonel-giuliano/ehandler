CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -pedantic -MMD -MP -I $(INCLUDE_DIR)

SRC_DIR 	= src
TEST_DIR 	= test
INCLUDE_DIR = include
BUILD_DIR 	= build

SRCS 		= $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS 	= $(wildcard $(TEST_DIR)/*.c)
OBJS 		= $(patsubst $(SRC_DIR)/%.c, 	$(BUILD_DIR)/%.o, $(SRCS))
TEST_OBJS 	= $(patsubst $(TEST_DIR)/%.c, 	$(BUILD_DIR)/%.o, $(TEST_SRCS))
DEPS 		= $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)


all: test


-include $(DEPS)


test: CFLAGS += -g -O0 -DLIBEH_DEBUG
test: $(OBJS) $(TEST_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@


clean:
	rm -rf $(BUILD_DIR)
