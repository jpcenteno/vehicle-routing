CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Wextra -pedantic -Werror #-Wconversion

OUT_DIR = build
SRC_DIR = src

# Expande a todos los .cpp en $(SRC_DIR)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)

all: $(OUT_DIR)/vrp

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	@[ -d $(dir $@) ] || mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUT_DIR)/vrp: $(OBJECTS)
	@[ -d $(dir $@) ] || mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(OUT_DIR)

