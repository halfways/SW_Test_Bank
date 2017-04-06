#include <stdio.h>

#define LIMIT 1000000

int queue[LIMIT][3];
int front, rear;
int N, map[110][110], visited[110][110];

int init();
int enqueue(int x, int y, int sum);
int dequeue(int *x, int *y, int *sum);
int check_visited(int x, int y, int sum);
int move();

int main(void) {
	int i, j;
	char c;

	init();

	scanf("%d\n", &N);

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			scanf("%c", &c);
			map[i][j] = c - '0';
		}
		scanf("%c", &c);
	}

	enqueue(0, 0, 0);

	while(1) {
		if(move())
			break;
	}

	printf("%d", visited[N - 1][N - 1]);

	return 0;
}

int init() {
	int i, j;
	for(i = 0; i < 110; i++) {
		for(j = 0; j < 110; j++) {
			map[i][j] = 0;
			visited[i][j] = -1;
		}
	}

	front = 0;
	rear = 0;

	return 0;
}

int enqueue(int x, int y, int sum) {
	if(check_visited(x, y, sum))
		return 0;

	queue[rear][0] = x;
	queue[rear][1] = y;
	queue[rear][2] = sum;
	rear++;

	if(rear == LIMIT)
		rear = 0;

	return 0;
}

int dequeue(int *x, int *y, int *sum) {
	if(front == rear)
		return 1;

	*x = queue[front][0];
	*y = queue[front][1];
	*sum = queue[front][2];
	front++;

	if(front == LIMIT)
		front = 0;

	return 0;
}

int check_visited(int x, int y, int sum) {
	if(visited[x][y] == -1)
		return 0;
	else if(visited[x][y] > sum + map[x][y])
		return 0;
	else
		return 1;
}

int move() {
	int x, y, sum;
	if(dequeue(&x, &y, &sum))
		return 1;

	sum += map[x][y];
	if((visited[x][y] == -1) || (visited[x][y] > sum))
		visited[x][y] = sum;
	else
		return 0;

	if(x < N -1)
		enqueue(x + 1, y, sum);
	if(y < N -1)
		enqueue(x, y + 1, sum);
	if(x > 0)
		enqueue(x - 1, y, sum);
	if(y > 0)
		enqueue(x, y - 1, sum);

	return 0;
}
