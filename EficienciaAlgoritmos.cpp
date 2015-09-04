

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <chrono>
#include <fstream>
#include <vector>



typedef std::chrono::microseconds micros;

//-----------------------------------Bubble Sort-----------------------//
void bubbleSort( int v[], int N){
    
    int temp;
    
    for (int i = 0; i < N; i++){
        for(int j= N-1; j>i; j--){
            if (v[j-1] > v[j])
            {
                temp = v[j-1];
                v[j-1] = v[j];
                v[j] = temp;
            }
        }
    }
}

//-----------------------------------Cocktail Sort-----------------------//
void cocktailSort(int v[], int N){
    int lo = 0, hi = (N-1), mov = lo, temp;
    
    while (lo<hi){
        for(int i=hi; i>lo; --i){
            if(v[i-1]>v[i]){
                temp = v[i-1];
                v[i-1]=v[i];
                v[i]= temp;
                mov=i;
            }
        }
        
        lo = mov;
        
        for(int i=lo; i<hi; ++i){
            if(v[i] > v[i+1]){
                temp = v[i];
                v[i] = v[i+1];
                v[i+1]= temp;
                mov = i;
            }
        }
        hi=mov;
    }
}

//-----------------------------------Insertion Sort-----------------------//
void insertionSort(int v[], int N){
    
    int index;
    
    for (int i=1; i < N; i++)
    {
        index = v[i];
        
        int j = i-1;
        
        while (j >= 0 && v[j] > index)
        {
            v[j + 1] = v[j];
            j--;
        }
        
        v[j+1] = index;
    }
    
}
//-----------------------------------Bucket Sort-----------------------//

void bucketSort(int v[], const int N){
    
    int m = 10001;
    int buckets[m];
    
    for(int i=0; i< m; ++i){
        buckets[i]=0;
    }
    
    for (int i = 0; i < N; ++i){
        ++buckets[v[i]];
    }
    
    for (int i =0, j = 0; j < m; ++j){
        for (int k = buckets[j]; k > 0; --k){
            v[i++] = j;
        }
    }
    
    
}

//-----------------------------------Merge Sort-----------------------//
void merge(int v[], int l, int m, int n, int N)
{
    int i, j, k;
    int aux[N];   //Vector auxiliar
    
    for(i=m+1;i>l;i--)
        aux[i-1] = v[i-1];
    
    for (j=m; j<n; j++)
        aux[n+m-j] = v[j+1];
    
    for(k=l;k<=n;k++)       //Mezcla
        if (!(aux[i]> aux[j])) // <
            v[k] = aux[i++];
        else
            v[k] = aux[j--];
}

void mergeSort(int v[], int l, int n, int N){
    int m = (n+l)/2;
    if (n > l)
    {
        mergeSort (v, l, m, N);
        mergeSort (v, m+1, n, N);
        merge (v, l, m, n, N);
    }
}

//-----------------------------------Radix Sort-----------------------//
int getMax(int v[], int N){
    
    int max = v[0];
    
    for(int i=1; i<N; i++){
        if(v[i]>max){
            max = v[i];
        }
    }
    
    return max;
}

void countSort(int v[], int N, int exp){
    int output[N];
    int count[10] = {0};
    
    
    for(int i=0; i<N; i++){
        count[(v[i]/exp)%10]++;
    }
    
    for(int i=1; i<10;i++){
        count[i]+=count[i-1];
    }
    
    for (int i = N-1; i>=0; i--){
        
        output[count[( v[i]/exp ) %10 ] -1] = v[i];
        count[(v[i]/exp)%10]--;
    }
    
    for(int i=0;i<N; i++){
        v[i]=output[i];
    }
}

void radixSort(int v[], int N){
    int m = getMax(v, N);
    
    for(int exp = 1; m/exp>0; exp*=10){
        countSort(v, N, exp);
    }
}

//--------------------------------Shell Sort------------------------------------//

void shellSort(int v[], int N){
    int temp;
    
    for(int gap= N/2; gap>0; gap/=2){
        for(int i=gap; i<N; i++){
            for(int j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap){
                temp = v[j];
                v[j]= v[j+gap];
                v[j+gap] = temp;
            }
        }
    }
}


//-----------------------------------Selection Sort-----------------------//
void selectionSort(int v[], int N){
    int minimo = 0;
    int temp;
    
    for(int i = 0; i < N-1; i++){
        minimo = i;
        for(int j = i + 1; j < N; j++){
            if (v[minimo] > v[j])
                minimo = j;
        }
        temp = v[minimo];
        v[minimo] = v[i];
        v[i] = temp;
    }
}


//-----------------------------------Quick Sort-----------------------//
void quickSort(int v[], int primero, int ultimo){
    int izquierdo = primero;
    int derecho = ultimo;
    int temp;
    
    //Se selecciona pivote
    int pivote = v[primero];
    
    if ( primero < ultimo) // Paso base
    {
        // particion
        while ( izquierdo < derecho)
        {
            while ( (izquierdo < derecho) && !(v[izquierdo] > pivote)) izquierdo++; // <=
            while (v[derecho]> pivote ) derecho--; // >
            
            if ( izquierdo < derecho) // se intercambian los contenidos
            {
                temp = v[derecho];
                v[derecho] = v[izquierdo];
                v[izquierdo] = temp;
            }
        }
        
        // Se intercambia el pivote con el elemento de la posición derecha
        temp = v[derecho];
        v[derecho] = v[primero];
        v[primero] = temp;
        
        // Paso recursivo
        quickSort ( v, primero, derecho-1);
        quickSort ( v, izquierdo, ultimo);
    }
}


//-----------------------------------Counting Sort-----------------------//


void findMinMax(int v[], int N, int& mi, int& max){
    mi = 100;
    max = 0;
    
    for( int i = 0; i < N; i++ ){
        if( v[i] > max ) max = v[i];
        if( v[i] < mi ) mi = v[i];
    }
    
}


void countingSort( int v[], int N){
    int mi, max;
    int z=0;
    findMinMax(v, N, mi, max);
    int nlen = (max-mi)+1;
    int* temp = new int[nlen];
    memset(temp, 0, nlen * sizeof( int ));
    
    for( int i = 0; i < N; i++ ){
        temp[v[i] - mi]++;
    }
    
    for( int i = mi; i <= max; i++ ){
        while( temp[i - mi] )
        {
            v[z++] = i;
            temp[i - mi]--;
        }
    }
    
    
    delete [] temp;
}

//-----------------------------------Heap Sort-----------------------//

void shift_down(int heap[],int i, int max) {
    int i_big, c1, c2;
    while(i < max) {
        i_big = i;
        c1 = (2*i) + 1;
        c2 = c1 + 1;
        if( c1<max && heap[c1]>heap[i_big] )
            i_big = c1;
        if( c2<max && heap[c2]>heap[i_big] )
            i_big = c2;
        if(i_big == i) return;
        swap(heap[i],heap[i_big]);
        i = i_big;
    }
}

void to_heap(int arr[], int N) {
    int i = (N/2) - 1;
    while(i >= 0) {
        shift_down(arr, i, N);
        --i;
    }
}

void heap_sort(int arr[], int N) {
    to_heap(arr, N);
    int end = N - 1;
    while (end > 0) {
        swap(arr[0], arr[end]);
        shift_down(arr, 0, end);
        --end;
    }
}

//-------------Print Algorithm Time------------
void printAlgorithm(std::string alg, micros dur)
{
    std::cout << alg << ": " << dur.count()<< " micros" << std::endl;
}

//-----------Fill File-------------
void fillFile(std::fstream & file)
{
    srand((int) time(NULL));
    std::cout << "Escribiendo 1,000,000 de valores al archivo" << std::endl;
    for (int i = 0; i < 1000000; ++i) {
        file << rand() % 10000 << endl;
    }
    std::cout << "Valores escritos correctamente" << std::endl;
}

//-----------Open File-------------
void openFile(std::fstream & log)
{
    if (fopen("./valores.txt", "r"))
    {
        std::cout << "Se encontró el archivo con los datos... Abriendo " << std::endl;
        log.open("./valores.txt", fstream::in);//abrir o crear el archivo
        return;
    }
    else
    {
        std::cout << "No se encontró el archivo con los datos... Creando uno nuevo" << std::endl;
        log.open("./valores.txt", fstream::out);//abrir o crear el archivo
        std::cout << "llenando valores" << std::endl;
        fillFile(log);
    }
    
}

//-----------------------------------Read values from file-----------------------//
void readValues(int* arr, int max, std::string path)
{
    std::ifstream file(path);
    int cont = 0;
    std::string line;
    while ( getline (file,line) )
    {
        arr[cont] = stoi(line);
        cont++;
        if(cont >= max)
            return;
    }
}

//-----------------------------------Binary Tree Node-----------------------//
struct Node {
    int val;
    Node* left;
    Node* right;
    
    Node(int n) {
        val = n;
        left = right = nullptr;
    }

    static void destroy(Node* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
};

//-----------------------------------Sorted Binary Tree Insert-----------------------//
void insert(Node*& node, int val)
{
    if (!node)
        node = new Node(val);
    else if (val < node->val)
        insert(node->left, val);
    else
        insert(node->right, val);
}

//-----------------------------------In Order Traversal-----------------------//
void inOrder(Node* node, std::vector<int>& a)
{
    if (node) {
        inOrder(node->left, a);
        a.push_back(node->val);
        inOrder(node->right, a);
    }
}

//-----------------------------------Binary Sort-----------------------//
void binarySort(int a[], int N)
{
    Node* root = nullptr;
    for (int i = 0; i < N; ++i)
        insert(root, a[i]);

    std::vector<int> aux;
    inOrder(root, aux);

    Node::destroy(root);

    for (int i = 0; i < aux.size(); ++i)
        a[i] = aux[i];
}

int main(int argc, const char * argv[]) {
    
    int N = 10;
    
    std::fstream textFile;
    
    openFile(textFile);
    
    int lim = 1000000;
    
    //Repetir desde N=10 hasta N=1000000
    while(N <= lim)
    {
        std::cout << "-------- " << N << " datos --------" << std::endl;
        //-----------------------------------Bucket Sort-----------------------//
        int* a = new int[N];
        readValues(a, N, "./valores.txt");
        auto begin = std::chrono::high_resolution_clock::now();
        bucketSort(a, N);
        auto end = std::chrono::high_resolution_clock::now();
        auto bucket = std::chrono::duration_cast<micros>(end-begin);
        printAlgorithm("Bucket Sort", bucket);
        delete a;
        
        //-----------------------------------Counting Sort-----------------------//
        a = new int[N];
        readValues(a, N, "./valores.txt");
        begin = std::chrono::high_resolution_clock::now();
        countingSort(a, N);
        end = std::chrono::high_resolution_clock::now();
        auto counting = std::chrono::duration_cast<micros>(end-begin);
        printAlgorithm("Counting Sort", counting);
        delete a;
        
        //-----------------------------------Merge Sort-----------------------//
        a = new int[N];
        readValues(a, N, "./valores.txt");
        begin = std::chrono::high_resolution_clock::now();
        mergeSort(a, 0, N-1, N);
        end = std::chrono::high_resolution_clock::now();
        auto merge = std::chrono::duration_cast<micros>(end-begin);
        printAlgorithm("Merge Sort", merge);
        delete a;
        
        //-----------------------------------Radix Sort-----------------------//
        a = new int[N];
        readValues(a, N, "./valores.txt");
        begin = std::chrono::high_resolution_clock::now();
        radixSort(a, N);
        end = std::chrono::high_resolution_clock::now();
        auto radix = std::chrono::duration_cast<micros>(end-begin);
        printAlgorithm("Radix Sort", radix);
        delete a;
        
        //-----------------------------------Shell Sort-----------------------//
        a = new int[N];
        readValues(a, N, "./valores.txt");
        begin = std::chrono::high_resolution_clock::now();
        shellSort(a, N);
        end = std::chrono::high_resolution_clock::now();
        auto shell = std::chrono::duration_cast<micros>(end-begin);
        printAlgorithm("Shell Sort", shell);
        delete a;
        
        //-----------------------------------Quick Sort-----------------------//
        a = new int[N];
        readValues(a, N, "./valores.txt");
        begin = std::chrono::high_resolution_clock::now();
        quickSort(a, 0, N-1);
        end = std::chrono::high_resolution_clock::now();
        auto quick = std::chrono::duration_cast<micros>(end-begin);
        printAlgorithm("Quick Sort", quick);
        delete a;
        
        //-----------------------------------Heap Sort-----------------------//
        a = new int[N];
        readValues(a, N, "./valores.txt");
        begin = std::chrono::high_resolution_clock::now();
        heap_sort(a, N);
        end = std::chrono::high_resolution_clock::now();
        auto heap = std::chrono::duration_cast<micros>(end-begin);
        printAlgorithm("Heap Sort", heap);
        delete a;

        //-----------------------------------Binary Tree Sort-----------------------//
        a = new int[N];
        readValues(a, N, "./valores.txt");
         begin = std::chrono::high_resolution_clock::now();
        binarySort(a, N);
         end = std::chrono::high_resolution_clock::now();
        auto binary = std::chrono::duration_cast<micros>(end-begin);
        printAlgorithm("Binary Sort", binary);
        delete a;

        //-----------------------------------Insertion Sort-----------------------//
        a = new int[N];
        readValues(a, N, "./valores.txt");
        begin = std::chrono::high_resolution_clock::now();
        insertionSort(a, N);
        end = std::chrono::high_resolution_clock::now();
        auto insertion = std::chrono::duration_cast<micros>(end-begin);
        printAlgorithm("Insertion Sort", insertion);
        delete a;

        //-----------------------------------Selection Sort-----------------------//
        a = new int[N];
        readValues(a, N, "./valores.txt");
        begin = std::chrono::high_resolution_clock::now();
        selectionSort(a, N);
        end = std::chrono::high_resolution_clock::now();
        auto selection = std::chrono::duration_cast<micros>(end-begin);
        printAlgorithm("Selection Sort", selection);
        delete a;

        //-----------------------------------Cocktail Sort-----------------------//
        a = new int[N];
        readValues(a, N, "./valores.txt");
        begin = std::chrono::high_resolution_clock::now();
        cocktailSort(a, N);
        end = std::chrono::high_resolution_clock::now();
        auto cocktail = std::chrono::duration_cast<micros>(end-begin);
        printAlgorithm("Cocktail Sort", cocktail);
        delete a;

        //-----------------------------------Bubble Sort-----------------------//
        a = new int[N];
        readValues(a, N, "./valores.txt");
         begin = std::chrono::high_resolution_clock::now();
        bubbleSort(a, N);
         end = std::chrono::high_resolution_clock::now();
        auto bubble = std::chrono::duration_cast<micros>(end-begin);
        printAlgorithm("Bubble Sort", bubble);
        delete a;

        N*=10;
        
    }
    return 0;
    
}
