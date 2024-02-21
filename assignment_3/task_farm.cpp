/*
  Assignment: Make an MPI task farm. A "task" is a randomly generated integer.
  To "execute" a task, the worker sleeps for the given number of milliseconds.
  The result of a task should be send back from the worker to the master. It
  contains the rank of the worker
*/

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <array>

// To run an MPI program we always need to include the MPI headers
#include <mpi.h>

const int NTASKS=5000;  // number of tasks
const int RANDOM_SEED=1234;
const int DONE=-1;

void master (int nworker) {
    std::array<int, NTASKS> task, result;
    // set up a random number generator
    std::random_device rd;
    //std::default_random_engine engine(rd());
    std::default_random_engine engine;
    engine.seed(RANDOM_SEED);
    // make a distribution of random integers in the interval [0:30]
    std::uniform_int_distribution<int> distribution(1, 30);

    for (int& t : task) {
        t = distribution(engine);   // set up some "tasks"
    }

    
    
    /*
    IMPLEMENT HERE THE CODE FOR THE MASTER
    ARRAY task contains tasks to be done. Send one element at a time to workers
    ARRAY result should at completion contain the ranks of the workers that did
    the corresponding tasks
    */
    int task_id = 0;
    MPI_Request send_req[NTASKS];
    for (int worker=1; worker<=nworker; worker++) {
        MPI_Isend(&task[task_id], 1, MPI_INT, worker, 0, MPI_COMM_WORLD, &send_req[task_id]); // Non-blocking send
        task_id++;
    }

    int completed_tasks = 0;
    while (completed_tasks < NTASKS) {
        int worker;
        MPI_Status st;
        MPI_Recv(&worker, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &st);
        result[completed_tasks] = worker;
            
        if (task_id < NTASKS) {
            // Send the next task
            MPI_Isend(&task[task_id], 1, MPI_INT, worker, 0, MPI_COMM_WORLD, &send_req[task_id]);
            task_id++;
        } else {
            MPI_Isend(&DONE, 1, MPI_INT, worker, 0, MPI_COMM_WORLD, &send_req[task_id]);
        }
    
        completed_tasks++;
    }

    
    
    
    //MPI_Waitall(NTASKS,recv_req,MPI_STATUSES_IGNORE);
    //MPI_Waitall(NTASKS,send_req,MPI_STATUSES_IGNORE);
    
    // Print out a status on how many tasks were completed by each worker
    for (int worker=1; worker<=nworker; worker++) {
        int tasksdone = 0; int workdone = 0;
        for (int itask=0; itask<NTASKS; itask++)
        if (result[itask]==worker) {
            tasksdone++;
            workdone += task[itask];
        }
        std::cout << "Master: Worker " << worker << " solved " << tasksdone << 
                    " tasks\n";   
    }

    for (int worker=1; worker<=nworker; worker++) {
        MPI_Request send_req;
        MPI_Isend(&DONE, 1, MPI_INT, worker, 0, MPI_COMM_WORLD, &send_req);
    }
    
    
}

// call this function to complete the task. It sleeps for task milliseconds
void task_function(int task) {
    std::this_thread::sleep_for(std::chrono::milliseconds(task));
}

void worker (int rank) {
    int task; 
    MPI_Request send_req, recv_req;
    while (true) {
        MPI_Irecv(&task, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &recv_req); // Non-blocking receive
        MPI_Wait(&recv_req, MPI_STATUS_IGNORE);
        //std::cout << rank << " receieved " << task << " from master \n";
        
        if (task == -1) break;

        MPI_Isend(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &send_req); // Non-blocking send
        
        task_function(task); // Execute the task
        
        
        MPI_Wait(&send_req, MPI_STATUS_IGNORE);
    }
}

int main(int argc, char *argv[]) {
    int nrank, rank;

    MPI_Init(&argc, &argv);                // set up MPI
    MPI_Comm_size(MPI_COMM_WORLD, &nrank); // get the total number of ranks
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // get the rank of this process

    if (rank == 0)       // rank 0 is the master
        master(nrank-1); // there is nrank-1 worker processes
    else                 // ranks in [1:nrank] are workers
        worker(rank);

    MPI_Finalize();      // shutdown MPI
}
