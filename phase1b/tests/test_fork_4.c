#include <phase1.h>
#include <phase1Int.h>
#include <assert.h>

// fork(): Process fork to higher priority process

static int
Child(void *arg) 
{
    char *msg = (char *) arg;

    USLOSS_Console("%s", msg);
    P1_Quit(11);
    // should not return
    return 0;
}
static int
Output(void *arg) 
{
    int rc, pid;
    char *msg = (char *) arg;

    USLOSS_Console("%s", msg);

    // Try forking process not sentinel with bad priority.
    rc = P1_Fork("Child", Child, "Hello World!\n", USLOSS_MIN_STACK, 6, 0, &pid);
    assert(rc == P1_INVALID_PRIORITY);

    P1_Quit(11);
    // should not return
    return 0;
}

void
startup(int argc, char **argv)
{
    int rc, pid;
    P1ProcInit();
    USLOSS_Console("startup\n");
    rc = P1_Fork("Hello", Output, "Hello World!\n", USLOSS_MIN_STACK, 2, 0, &pid);
    assert(rc == P1_SUCCESS);
    // P1_Fork should not return
    assert(0);
}

void test_setup(int argc, char **argv) {}

void test_cleanup(int argc, char **argv) {}

void finish(int argc, char **argv) {}