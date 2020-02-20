part1:
	gcc part1.c -o part1.out -lpthread

part2:
	gcc main.c node.c queue.c -o part2.out

clean:
	-rm part1.out part2.out cpu_scheduling_output_file.txt