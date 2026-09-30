# ============================================================
#  Makefile — DataStructure 项目
# ============================================================

CC     = g++
CXX    = g++
CXXFLAGS = -Wall -g -O2 -std=c++17 -Iinclude
SRC_DIR = src
BUILD_DIR = build
OUT_DIR = build

# 找所有 .cpp 文件
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
# 转换为 build 路径
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
# 转换为可执行文件路径（去掉 .cpp 扩展名，改为在 build/ 目录下）
PROGS = $(SRCS:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%)

# ============================================================
# 规则
# ============================================================

all: $(PROGS)

# 可执行文件
$(OUT_DIR)/%: $(BUILD_DIR)/%.o | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# 编译 .cpp → .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 创建目录
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(BUILD_DIR) $(OUT_DIR)

.PHONY: all clean
