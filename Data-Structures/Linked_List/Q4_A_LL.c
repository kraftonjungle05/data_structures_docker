#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode {
    int item;
    struct _listnode *next;
} ListNode; // 구조체 정의 (한 번만)

typedef struct _linkedlist {
    int size;
    ListNode *head;
} LinkedList;

//////////////////////// 함수 선언 //////////////////////////////////////////////

// You should not change the prototype of this function
void moveEvenItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////// main ////////////////////////////////////////////////////

int main()
{
    LinkedList ll;
    int c, i, j;
    c = 1;

    ll.head = NULL;
    ll.size = 0;

    printf("1: Insert an integer to the linked list:\n");
    printf("2: Move all even integers to the back of the linked list:\n");
    printf("0: Quit:\n");

    while (c != 0)
    {
        printf("Please input your choice(1/2/0): ");
        scanf("%d", &c);

        switch (c)
        {
        case 1:
            printf("Input an integer that you want to add to the linked list: ");
            scanf("%d", &i);
            j = insertNode(&ll, ll.size, i);
            printf("The resulting linked list is: ");
            printList(&ll);
            break;

        case 2:
            moveEvenItemsToBack(&ll); // 구현된 함수 호출
            printf("The resulting linked list after moving even integers to the back is: ");
            printList(&ll);
            removeAllItems(&ll);
            break;

        case 0:
            removeAllItems(&ll);
            break;

        default:
            printf("Choice unknown;\n");
            break;
        }
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// 핵심 구현 함수
void moveEvenItemsToBack(LinkedList *ll)
{
    if (ll == NULL || ll->head == NULL)
        return;

    ListNode *cur = ll->head, *prev = NULL;
    ListNode *tail = ll->head;

    while (tail->next != NULL)
        tail = tail->next;

    ListNode *end = tail;

    while (cur != NULL && cur != end->next)
    {
        ListNode *next = cur->next;
        if (cur->item % 2 == 0)
        {
            // 짝수면 뒤로 이동
            if (prev == NULL)
                ll->head = next;
            else
                prev->next = next;

            tail->next = cur;
            cur->next = NULL;
            tail = cur;
        }
        else
        {
            prev = cur;
        }
        cur = next;
    }
}

//////////////////////////////////////////////////////////////////////////////////
// 기본 제공 함수들
void printList(LinkedList *ll)
{
    ListNode *cur;
    if (ll == NULL)
        return;

    cur = ll->head;

    if (cur == NULL)
        printf("Empty");

    while (cur != NULL)
    {
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

void removeAllItems(LinkedList *ll)
{
    ListNode *cur = ll->head;
    ListNode *tmp;

    while (cur != NULL)
    {
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }

    ll->head = NULL;
    ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index)
{
    if (ll == NULL || index < 0 || index >= ll->size)
        return NULL;

    ListNode *temp = ll->head;

    while (index > 0)
    {
        temp = temp->next;
        if (temp == NULL)
            return NULL;
        index--;
    }

    return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{
    ListNode *pre, *cur;

    if (ll == NULL || index < 0 || index > ll->size)
        return -1;

    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->item = value;

    if (index == 0)
    {
        newNode->next = ll->head;
        ll->head = newNode;
    }
    else
    {
        pre = findNode(ll, index - 1);
        if (pre == NULL)
        {
            free(newNode);
            return -1;
        }
        newNode->next = pre->next;
        pre->next = newNode;
    }

    ll->size++;
    return 0;
}

int removeNode(LinkedList *ll, int index)
{
    ListNode *pre, *cur;

    if (ll == NULL || index < 0 || index >= ll->size)
        return -1;

    if (index == 0)
    {
        cur = ll->head;
        ll->head = cur->next;
    }
    else
    {
        pre = findNode(ll, index - 1);
        if (pre == NULL || pre->next == NULL)
            return -1;

        cur = pre->next;
        pre->next = cur->next;
    }

    free(cur);
    ll->size--;
    return 0;
}