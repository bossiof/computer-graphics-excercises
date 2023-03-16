CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
VulkanTest: A00.cpp
	g++ $(CFLAGS) -o -I headers/ -I$VP/include/ VulkanTest A00.cpp $(LDFLAGS)


