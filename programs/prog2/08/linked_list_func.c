#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct {
    int no;
    char name[32];
} Data;
 
typedef struct _node {
    Data data;
    struct _node *next;
} Node;
 
typedef struct {
    Node *head;
    Node *tail;
} LinkedList;
 
/* リストの要素ひとつ分のメモリを確保し、メンバ変数の値を代入 */
Node *CreateNode(int no, const char *name)
{
    Node *n = (Node *)malloc(sizeof(Node));
 
    if (n == NULL)
    {
        fprintf(stderr, "CreateNode: error: memory allocation failed\n");
        return NULL;
    }
 
    n->data.no = no;
    strcpy(n->data.name, name);
 
    return n;
}
 
/* リストの要素の表示 */
void PrintNode(Node *node)
{
    printf("no: %d, name: %s\n", node->data.no, node->data.name);
}
 
/* リストを初期化 */
void ListInit(LinkedList *list)
{
    list->head = NULL;   /* リストの先頭を NULL に */
    list->tail = NULL;   /* リストの末尾を NULL に */
}
 
/* リストの末尾に要素を追加 */
void ListAddTail(LinkedList *list, Node *node)
{
    if (list->head == NULL) /* 要素がまだないとき */
    {
        /* 要素をひとつ追加すると、それが先頭かつ末尾になる */
        list->head = node;
        node->next = NULL;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        node->next = NULL;
        list->tail = node;
    }
}
 
/* リストの先頭を削除 */
void ListDeleteHead(LinkedList *list)
{
    if (list->head == NULL)
    {
        /* 要素がないなら何もする必要がない */
        return;
    }
    else
    {
        Node *next = list->head->next; /* 先頭の次の要素へのアドレスを保持 */
 
        /* 先頭を削除…削除の前に次の要素へのアドレスを記憶しておかないと削除したら失われる */
        free(list->head);
 
        /* 新しい先頭要素として、元々の先頭の次の要素を設定 */
        list->head = next;
 
        /* 先頭を削除して要素がなくなった場合、末尾も NULL にする */
        if (list->head == NULL)
            list->tail = NULL;
    }
}
 
/* リストを表示 */
void ListPrint(LinkedList *list)
{
    if (list->head == NULL)
    {
        puts("(null)\n");
    }
    else
    {
        Node *p = list->head;
 
        while ( p != NULL )
        {
            PrintNode(p);
            p = p->next;
        }
        putchar('\n');
    }
}
 
/* リストの要素を削除 */
void ListClear(LinkedList *list)
{
    Node *p = list->head;
 
    while ( p != NULL )
    {
        Node *tmp = p;  /* 現在のノードへのポインタを保存しておく */
        p = p->next; /* p を先に進める…進める前に p を解放するとリストを辿るためのポインタも失われる */
        free(tmp);      /* 現在のノードのメモリを解放する */
    }
 
    /* リストを初期化して、次の利用に備える */
    ListInit(list);
}

void ListDeleteTail(LinkedList *list){
  if(list->head == NULL){
    return;
  }
  else if(list->head == list->tail){ //要素が一個の時
    free(list->head);
  }
  else{
    Node *next = list->head->next; 
    Node *now = list->head;
    
   
    while(next->next != NULL){
      
      now = next;
      next = next->next;
    }
    //nowがtailの一個前のノードのアドレス

    free(list->tail);
    list->tail = now;
    list->tail->next = NULL;
 
    
  }
}

void ListAddHead(LinkedList *list, Node *node){
  if (list->head == NULL) /* 要素がまだないとき */
    {
      /* 要素をひとつ追加すると、それが先頭かつ末尾になる */
      list->head = node;
      node->next = NULL;
      list->tail = node;
    }
  else{
    node->next = list->head;
    list->head = node;
    //list->tail->next = NULL; //いらんきがす
  }
}



 
int main(void)
{
    LinkedList list;
 
    ListInit(&list);
 
    ListAddTail(&list, CreateNode(100, "Yamada"));
    ListAddTail(&list, CreateNode(200, "Suzuki"));
    ListAddTail(&list, CreateNode(300, "Sato"));
 
    ListPrint(&list);
 
    ListDeleteHead(&list);
 
    puts("head deleted: ");
 
    ListPrint(&list);




    ListDeleteTail(&list);
    
    puts("tail deleted: ");
    
    ListPrint(&list);




    
    ListAddHead(&list, CreateNode(100, "Nagata"));
    
    puts("head appended: ");
    
    ListPrint(&list);
    
    ListClear(&list);
 
    return 0;
}
