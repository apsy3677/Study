// zombie_demo.cpp: what happens to a child that exits before its parent collects its exit status.
// Build: g++ -std=c++17 -o zombie_demo zombie_demo.cpp
// Run:   ./zombie_demo zombie   (parent never waits -> child shows as Z <defunct> for 20 s)
//        ./zombie_demo wait     (parent calls waitpid -> child disappears at once)
//        ./zombie_demo orphan   (parent exits first -> child gets a new parent)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    const char* mode = argc > 1 ? argv[1] : "zombie";
    setvbuf(stdout, nullptr, _IONBF, 0);                 // 0. unbuffered, so lines appear even when piped
    pid_t pid = fork();                                  // 1. clone: returns 0 in the child, the child's pid in the parent
    if (pid == 0) {                                      // 2. child
        if (strcmp(mode, "orphan") == 0) {
            printf("child %d: parent is %d\n", getpid(), getppid());
            sleep(3);                                    //    outlive the parent
            printf("child %d: parent is now %d\n", getpid(), getppid());
            return 0;
        }
        printf("child %d: exiting with status 7\n", getpid());
        exit(7);                                         // 3. memory freed; kernel keeps pid + status 7 for the parent
    }
    printf("parent %d: forked child %d\n", getpid(), pid);
    if (strcmp(mode, "orphan") == 0) return 0;           //    parent leaves first
    if (strcmp(mode, "wait") == 0) {
        int status = 0;
        waitpid(pid, &status, 0);                        // 4. collect the status -> kernel deletes the child's entry
        printf("parent: child %d exited with %d\n", pid, WEXITSTATUS(status));
    }
    fflush(stdout);
    sleep(20);                                           // 5. look with: ps -o pid,ppid,stat,cmd
}
