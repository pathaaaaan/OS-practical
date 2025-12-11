#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct PageTable
{
    int frame_no;
    bool valid;
};

bool isPagePresent(struct PageTable *PT, int page, int pt_size)
{
    if (page < 0 || page >= pt_size)
        return false;
    return PT[page].valid;
}

void updatePageTable(struct PageTable *PT, int page, int fr_no, int status, int pt_size)
{
    if (page < 0 || page >= pt_size)
        return;
    PT[page].valid = (status == 1) ? true : false;
    PT[page].frame_no = fr_no;
}

void printFrameContents(int frame[], int no_of_frames)
{
    for (int i = 0; i < no_of_frames; i++)
    {
        if (frame[i] == -1)
            printf("- ");
        else
            printf("%d ", frame[i]);
    }
    printf("\n");
}

int main()
{
    int no_of_frames, n;
    if (scanf("%d", &no_of_frames) != 1)
        return 0; // first line: frames
    if (scanf("%d", &n) != 1)
        return 0; // second line: number of requests

    if (no_of_frames <= 0 || n <= 0)
    {
        printf("Frames and number of requests must be positive.\n");
        return 0;
    }

    int *reference_string = (int *)malloc(n * sizeof(int));
    if (!reference_string)
    {
        perror("malloc");
        return 1;
    }

    int max_page = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &reference_string[i]);
        if (reference_string[i] < 0)
            reference_string[i] = 0;
        if (reference_string[i] > max_page)
            max_page = reference_string[i];
    }

    int pt_size = max_page + 1;
    struct PageTable *PT = (struct PageTable *)malloc(pt_size * sizeof(struct PageTable));
    if (!PT)
    {
        perror("malloc");
        free(reference_string);
        return 1;
    }

    for (int i = 0; i < pt_size; i++)
    {
        PT[i].valid = false;
        PT[i].frame_no = -1;
    }

    int *frame = (int *)malloc(no_of_frames * sizeof(int));
    if (!frame)
    {
        perror("malloc");
        free(reference_string);
        free(PT);
        return 1;
    }
    for (int i = 0; i < no_of_frames; i++)
        frame[i] = -1;

    int page_fault = 0;
    int current = 0; // FIFO pointer: next frame to replace
    printf("*The Contents inside the Frame array at different time:*\n");

    for (int i = 0; i < n; i++)
    {
        int page = reference_string[i];

        if (!isPagePresent(PT, page, pt_size))
        {
            page_fault++;

            // check for an empty frame
            int empty_idx = -1;
            for (int f = 0; f < no_of_frames; f++)
            {
                if (frame[f] == -1)
                {
                    empty_idx = f;
                    break;
                }
            }

            if (empty_idx != -1)
            {
                // place in empty frame
                frame[empty_idx] = page;
                updatePageTable(PT, page, empty_idx, 1, pt_size);
            }
            else
            {
                // replace using FIFO pointer 'current'
                int old = frame[current];
                if (old >= 0 && old < pt_size)
                    updatePageTable(PT, old, -1, 0, pt_size);
                frame[current] = page;
                updatePageTable(PT, page, current, 1, pt_size);
                current = (current + 1) % no_of_frames;
            }
            printFrameContents(frame, no_of_frames);
        }
        // if page present -> hit -> do nothing
    }

    printf("\nTotal No. of Page Faults = %d\n", page_fault);
    printf("Page Fault ratio = %.2f\n", (float)page_fault / n);
    printf("Page Hit Ratio = %.2f\n", (float)(n - page_fault) / n);

    free(reference_string);
    free(PT);
    free(frame);
    return 0;
}