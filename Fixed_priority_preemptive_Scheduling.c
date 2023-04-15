#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int pid; // process ID
    int arrival_time; // arrival time of process
    int burst_time; // burst time of process
    int remaining_time; // remaining time to complete
} process;

void main() {
    int n, i, j, current_time, complete = 0, shortest_process, shortest_time = 9999;
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process p = (process) malloc(n * sizeof(process));
    int waiting_time = (int) malloc(n * sizeof(int));
    int turnaround_time = (int) malloc(n * sizeof(int));
    printf("Enter arrival time and burst time for each process:\n");
    for(i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
    }
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(current_time = 0; complete != n; current_time++) {
        shortest_process = -1;
        shortest_time = 9999;
        for(i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && p[i].remaining_time < shortest_time && p[i].remaining_time > 0) {
                shortest_process = i;
                shortest_time = p[i].remaining_time;
            }
        }
        if(shortest_process == -1) {
            printf("Idle\n");
            continue;
        }
        p[shortest_process].remaining_time--;
        if(p[shortest_process].remaining_time == 0) {
            complete++;
            int turnaround = current_time + 1 - p[shortest_process].arrival_time;
            int waiting = turnaround - p[shortest_process].burst_time;
            avg_waiting_time += waiting;
            avg_turnaround_time += turnaround;
            printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[shortest_process].pid, p[shortest_process].arrival_time, p[shortest_process].burst_time, waiting, turnaround);
            waiting_time[shortest_process] = waiting;
            turnaround_time[shortest_process] = turnaround;
        }
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    printf("\nAverage Waiting Time: %f\nAverage Turnaround Time: %f\n", avg_waiting_time, avg_turnaround_time);
}
