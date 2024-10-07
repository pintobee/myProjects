
// Andrea Pinto P7 Block Access Algorithms

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//function prototypes
int fcfs(int head, int requests[], int n);
int sstf(int head, int requests[], int n);
int look(int head, int requests[], int n);
int clook(int head, int requests[], int n);


// calculates total seek time for fcfs
int fcfs(int head, int requests[], int n) {
  int totalSeek = 0;
  for (int i = 0; i < n; i++) {
    totalSeek += abs(requests[i] - head);
    head = requests[i];
  }
  return totalSeek;
}

// calculates total seek time for sstf
int sstf(int head, int requests[], int n) {
  int totalSeek = 0;
  int *visited = calloc(n, sizeof(int));
  for (int i = 0; i < n; i++) {
    int closest = -1;
    int minDistance = INT_MAX;

    for (int j = 0; j < n; j++) {
      if (!visited[j]) {
        int distance = abs(requests[j] - head);
        if (distance < minDistance) {
          minDistance = distance;
          closest = j;
        }
      }
    }
    totalSeek += minDistance;
    head = requests[closest];
    visited[closest] = 1;
  }
  free(visited);
  return totalSeek;
}

// calculates total seek time for look
int look(int head, int requests[], int n) {
  int totalSeek = 0;
  int *visited = calloc(n, sizeof(int));
  int direction = 1;
  int completed = 0;

  while (completed < n) {
    int closest = -1;
    int minDistance = INT_MAX;

    for (int j = 0; j < n; j++) {
      if (!visited[j]) {
        int distance = requests[j] - head;
        if ((direction == 1 && distance >= 0) || (direction == -1 && distance <= 0)) {
          distance = abs(distance);
          if (distance < minDistance) {
            minDistance = distance;
            closest = j;
          }
        }
      }
    }
    if (closest == -1) {
      direction *= -1; //reverse
    } else {
      totalSeek += minDistance;
      head = requests[closest];
      visited[closest] = 1;
      completed++;
    }
  }
  free(visited);
  return totalSeek;
}

// calculates total seek time for c-look
int clook (int head, int requests[], int n) {
  int totalSeek = 0;
  int *visited = calloc(n, sizeof(int));
  int completed = 0;

  while (completed < n) {
    int closest = -1;
    int minDistance = INT_MAX;
    for (int j = 0; j < n; j++) {
      if (!visited[j]) {
        int distance = requests[j] - head;
        if (distance >= 0 && distance < minDistance) {
          minDistance = distance;
          closest = j;
        }
      }
    }
    if (closest == -1) {
      int minRequest = INT_MAX; // jumps to first request
      for (int j = 0; j < n; j++) {
        if (!visited[j] && requests[j] < minRequest) {
          minRequest = requests[j];
          closest = j;
        }
      }
      totalSeek += abs(head - requests[closest]);
    } else {
      totalSeek += minDistance;
    }
    head = requests[closest];
    visited[closest] = 1;
    completed++;
  }
  free(visited);
  return totalSeek;
}

int main() {
  int requests[100];
  int n = 0;
  while (scanf("%d", &requests[n]) == 1) {
    n++;
  }
  int head = requests[0];
  printf("Assignment 7: Block Access Algorithm\n");
  printf("By Andrea Pinto\n\n");
  printf("FCFS Total Seek: %d\n", fcfs(head, requests + 1, n - 1));
  printf("SSTF Total Seek: %d\n", sstf(head, requests + 1, n - 1));
  printf("LOOK Total Seek: %d\n", look(head, requests + 1, n - 1));
  printf("C-LOOK Total Seek: %d\n", clook(head, requests + 1, n - 1));

  return 0;
}
