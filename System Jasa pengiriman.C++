#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0
#define MAX_PARTAI 3
#define TRUCK_SIZE 8
using namespace std;


//void ADT
//void stuck
//void queue
//void sorting termasuk sorting bubble


void menu ()
{
			printf ("\n=======================================================\n");
			printf ("\n --- Aplikasi System Antrian Jasa Pengiriman Barang ---\n");
			printf ("\n======================================================\n\n");
			printf ("Oleh : Kelompok 7 \n");
			printf ("\n");

		printf("\t|=========================================|\n");
        printf("\t|Selamat Datang                           |\n"); 
        printf("\t|=========================================|\n");
        printf("\t|Menu User :                              |\n");
        printf("\t|=========================================|\n");
        printf("\t|1. Input barang ke gudang                |\n");
        printf("\t|2. Hapus barang dari daftar antrian      |\n");
        printf("\t|3. Masukkan barang ke truck partai       |\n");
        printf("\t|4. Cek barang di antrian                 |\n");
        printf("\t|5. Cek barang di area truk               |\n");
       	printf("\t|6. Keluar                                |\n");
        printf("\t|=========================================|\n");
        printf("\t|Masukan inputan anda :    ");
}
//Fungsi atribut barang yang masuk ke dalam antrian untuk mengatur barang mana yang akan masuk sesuai urutan
typedef struct barang_queue
{
    int data;
    char nama_pengirim[50], nama_penerima[50], alamat_tujuan[50], jenis_paket[50];
    struct barang_queue *next;
} barang_queue;

//mendefinisikan untuk menjalakan atribut barang yang masuk ke dalam stack yang dijadikan satu di dalam struct ini
typedef struct barang_stack
{
    int data;
    char nama_pengirim[50], nama_penerima[50], alamat_tujuan[50], jenis_paket[50];
    struct barang_stack *next; //  memerintahkan pointer suatu barang pada tumpukan yang sebelumnya
    struct barang_stack *prev; // memerintahkan pointer suatu barang pada tumpukkan yanng selanjutnya
} barang_stack;
barang_stack *top = NULL; 

typedef struct queue
{
    int count;
    barang_queue *front; //   pointer variabel tipe data barang_queue yang akan menunjuk elemen paling depan
    barang_queue *rear;  // pointer variabel tipe data barang_stack yang akan menunjuk elemen paling belakang
} queue;
// Mengecek apakah stack dalam keadaan kosong atau tidak
int isEmpty()
{
    if (top == NULL)
        return 1;
    else
        return 0;
}

void push(int weight, char send[], char accept[], char address[], char type[])
{
    barang_stack *temp = (barang_stack *) malloc(sizeof(barang_stack));
    temp->prev = NULL; 
    temp->next = NULL;
    temp->data = weight;
    strcpy(temp->nama_pengirim, send); //untuk melakukan penyalinan data dari kolom sintaks sebelumnya ke kolom berikutnya
    strcpy(temp->nama_penerima, accept);
    strcpy(temp->alamat_tujuan, address);
    strcpy(temp->jenis_paket, type);
    if (isEmpty() == 1) // apabila stack pada barang dalam keadaan kosong 
    {
        top = temp; 
    }
    else
    {
        top->next = temp; 
        temp->prev = top; // posisi top saat ini berada pada  prev atau next
        top = temp; 
    }
}
//melakukan fungsi pop
void pop ()
{
    barang_stack *remove;
    remove = top;
    if (isEmpty() == 1)
    {
        printf("Tidak ada DATA barang dalam antrian\n");
    }
    else
    {
        top = top->prev;
        free(remove);
    }
}
//menampilkan isi dari stack tersebut
void display_stack()
{   //mendeklarasikan sebuah pointer dengan tipe data barang_stack
    barang_stack *help;
    help = top;
    if (isEmpty() == 1) // jika stack dalam keadaan kosong maka masuk ke dalam pengkondisian ini 
    {
        printf("\t --KOSONG--\n");
    }
    else
    { //Dengan memakai linked list
        while (help != NULL)
        {
        	printf("\t ---- DATA STACK BARANG ----\n\n");
            printf("\t ===================================\n");
            printf("\t Nama Pengirim :      %s\n", help->nama_pengirim);
            printf("\t Nama Penerima :      %s\n", help->nama_penerima);
            printf("\t Alamat Penerima :    %s\n", help->alamat_tujuan);
            printf("\t Jenis Barang :       %s\n", help->jenis_paket);
            printf("\t Berat Barang :       %d\n", help->data);
            printf("\t ===================================\n");
            help = help->prev; 
        }
    }
}
// melakukan eksekusi dan inisialiasi pada queue 
void initialize(queue *q)
{
    q->count = 0;
    q->front = NULL; 
    q->rear = NULL;
}
// cek apakah queue dalam keadaan kosong 
int isempty(queue *q)
{
    return (q->rear == NULL); 
}

void enqueue(queue *q)
{
    if (q->count < TRUCK_SIZE)
    {
        barang_queue *tmp;
        tmp = (barang_queue*)malloc(sizeof(barang_queue)); //alokasikan memori ke queue
        printf("\t Masukkan nama pengirim : ");
        fflush(stdin);
        scanf("%[^\n]s", tmp->nama_pengirim);
        printf("\t Masukkan nama penerima : ");
        fflush(stdin);
        scanf("%[^\n]s", tmp->nama_penerima);
        printf("\t Masukkan alamat tujuan : ");
        fflush(stdin);
        scanf("%[^\n]s", tmp->alamat_tujuan);
        printf("\t Jenis Barang :  ");
        fflush(stdin);
        scanf ("%[^\n]s", tmp->jenis_paket);
        printf("\t Masukkan berat : ");
        fflush(stdin);
        scanf("%d", &tmp->data);
        tmp->next = NULL;
        if (!isempty(q)) 
        {
            q->rear->next = tmp; 
            q->rear = tmp; 
        }
        else
        {
        
            q->front = q->rear = tmp;
        }
        q->count++; //lakukan perhitungan untuk program sebelum melakukan increment
        printf ("\n*****  Tekan enter untuk melanjutkan  ******\n");
    }
    else
    {
        printf("\t Antrian sudah PENUH!\n"); // jika count sudah tidak lagi memenuhi syarat maka cetak bagian ini
		printf ("\t Mohon untuk melakukan REMOVE untuk daftar antrian yang tidak diperlukan\n"); // informasi perintah solusi untuk user agar bisa mengubah daftar antrian
    }
}
// melakukan proses penghapusan
int dequeue(queue *q)
{
    barang_queue *tmp;
    int n = q->front->data;
    tmp = q->front;
    q->front = q->front->next; // data yang ada di now + 1 akan dipindahkan ke dalam data terkini
    q->count--; // kemudian variabel count bisa dikurangin
    free(tmp); // pointer tmp tersebut kemudian dihapus 
    return (n);
}
// menampilkan semua data barang yang ada di dalam queue
void display(barang_queue *head)
{
    if (head == NULL)
    {
        printf("\t Tidak Ada Penambahan Barang\n");
    }
    else
    {
        printf("\t DATA PENGIRIM DAN PENERIMA\n");
        printf("\t NAMA PENGIRIM : %s\n", head->nama_pengirim);
        printf("\t NAMA PENERIMA : %s\n", head->nama_penerima);
        printf("\t ALAMAT PENERIMA : %s\n", head->alamat_tujuan);
        printf("\t JENIS BARANG : %s\n", head->jenis_paket);
        printf("\t BERAT BARANG : %d\n", head->data);
        printf("\t ===================================\n");
        display(head->next); // memanggil fungsi kembali untuk melakukan perulangan
    }
}
//melakukan proses swap queue untuk implementasikan pada bubble sort
void swap(barang_queue *a, barang_queue *b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}
//melakukan teknik sorting
void bubble_sort(barang_queue *start)
{
    int swapped, i;
    barang_queue *ptr1;
    barang_queue *lptr = NULL;

    if (start == NULL)
    {
        return;
    }
    do
    {
        swapped = 0;
        ptr1 = start;
        while (ptr1->next != lptr) 
        {
            if (ptr1->data > ptr1->next->data) 
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

//melakukan proses penampilan
void display_sort(barang_queue *head)
{
    if (head == NULL) //apabila antrian dalam keadaan kosong
    {
        printf(" ");
    }
    else // apabila antrian tidak dalam keadaan kosong
    {
        printf("\t --%d\n", head->data);
        display_sort(head->next);
    }
}
//melakukan proses pencarian
void search(barang_queue *start, char *dicari)
{
    barang_queue *p;
    int post = 1;
    p = start; 
    while (p != NULL) //selanjtnya pointer p masih ke pointer alammat memori 
    {
        if (strcmp(p->nama_pengirim, dicari) == 0) // lakukan proses perbandingan dengan fungsi strcmpm dan jika bernilai 0 maka lakukan ke penkondisian terkini 
        {
            printf("\t Barang yang dikirim oleh %s ditemukan diposisi %d\n", dicari, post); //menampilkan indeks urutan di dalam program melalui post 
            return;
        }
        p = p->next;
        post++;
    }
    printf("\t Barang yang dikirim oleh %s tidak ditemukan\n", dicari);
}
// tampilan menu utama 
int main()
{	int profile (); 
    int ch, choice, post, i, j;
    int banyak_partai = 1;
    int banyak_barang = 1;
    char qty[50];
    queue *q;
    q = (queue*)malloc(sizeof(queue));
    initialize(q);
    while (banyak_partai <= MAX_PARTAI)
    {	menu();
        scanf("%d", &ch);
        if (ch == 1)
        {
            printf("\t Masukkan data dari barang\n");
            enqueue(q);
            banyak_barang++;
            printf("\t=================================\n");
        }
        else if (ch == 2)
        {
            dequeue(q);
        }
        else if (ch == 3)
        {
            barang_queue *help;
            help = q->front;
            do
            {
                push(help->data, help->nama_pengirim, help->nama_penerima, help->alamat_tujuan, help->jenis_paket);
                help = help->next;
            } while (help != NULL);
            printf("\t Barang berhasil dimasukan ke truk\n");
        }
        else if (ch == 4)
        {
            printf("\t ===================================\n");
            display(q->front);
        }
        else if (ch == 5)
        {
            display_stack();
        }
       
       
        else if (ch == 6)
        {
            break;
        }
   }
   return 0;
}
