#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Tree {
    int ogrenciNo;
    char isim[50];
    char soyIsim[50];
    int yas;
    struct Tree *left;
    struct Tree *right;
    int height;
} Tree;

void inorderTraversal(struct Tree *root);
void preorderTraversal(struct Tree *root);
void postorderTraversal(struct Tree *root);
void printLeaves(struct Tree *root);

struct Tree *minValueNode(struct Tree *root);
struct Tree *sagaDondur(struct Tree *y);
struct Tree *solaDondur(struct Tree *x);
struct Tree *findMax(struct Tree *node);
struct Tree *findMin(struct Tree *node);
struct Tree *newNode(int ogrenciNo, char *isim, char *soyIsim, int yas);
struct Tree *insert(struct Tree *node, int ogrenciNo, char *isim, char *soyIsim, int yas);
struct Tree *findNode(struct Tree *root, int ogrenciNo);
struct Tree *minValueNode(struct Tree *node);
struct Tree *findRoot(struct Tree *root);
struct Tree *deleteNode(struct Tree *root, int ogrenciNo);

int compareogrenciNos(int num1, int num2);
int max(int x, int y);
int height(struct Tree *node);
int balanceGet(struct Tree *node);
int getNodeCountFromNode(struct Tree *node);
int getNodeCount(struct Tree *root, int istenenOgrenciNo);
int Kok(struct Tree *node);
int SolCocuguOlan(struct Tree *root);
int SagCocuguOlan(struct Tree *root);
int Yaprak(struct Tree *root);
int SagveSolCocuguOlan(struct Tree *root);

int main() {
    struct Tree *root = NULL;

    FILE *dosya;
    dosya = fopen("kayit.txt", "r");

    if (dosya == NULL) {
        printf("Dosya Acilamadi.\n");
        return 1;
    }

    int ogrenciNo, yas;
    char isim[50], soyIsim[50];
    while (!feof(dosya)) {
        fscanf(dosya, "%d\t%s\t%s\t%d", &ogrenciNo, isim, soyIsim, &yas);
        root = insert(root, ogrenciNo, isim, soyIsim, yas);
    }
    
    printf("\nAVL Agaci'nin ilk hali(Inorder):\n");
    inorderTraversal(root);

    fclose(dosya);
    while (1) {
        printf("\n1-Yeni bir ogrenci kaydi ekleme islemi\n2-Inorder Siralama\n3-Preorder Siralama\n4-Postorder Siralama\n5-Silme Islemleri\n6-Subtreede uzerinde kac adet dugum var onu yazdirma\n7-Subtreede uzerinde en kucuk en buyuk dugumu yazdirma\n8-Yapraklari yazdirma\n9-Cikis\n");
        printf("Bu sayilardan birini seciniz(1, 2, 3, 4, 5, 6, 7, 8, 9):\n");
        int secim;
        scanf("%d", &secim);
        
        if(secim==1){
        	printf("Eklemek istediginiz ogrencinin ogrNonu giriniz:");
        	scanf("%d", &ogrenciNo);
                
			printf("Eklemek istediginiz ogrencinin adini giriniz:");
            scanf("%s", isim);
                
            printf("Eklemek istediginiz ogrencinin soyadini giriniz:");
            scanf("%s", soyIsim);

            printf("Eklemek istediginiz ogrencinin yasini giriniz:");
            scanf("%d", &yas);
                
            root = insert(root, ogrenciNo, isim, soyIsim, yas);
            printf("\nYeni dugum eklendikten sonra AVL Agaci (Inorder):\n");
            inorderTraversal(root);
		}
         
		else if(secim==2){
			printf("\nAVL Agaci (Inorder):\n");
            inorderTraversal(root);	
		}     
        
        else if(secim==3){
			printf("\nAVL Agaci (Preorder):\n");
            preorderTraversal(root);
            
		}    
        else if(secim==4){
			printf("\nAVL Agaci (Postorder):\n");
            postorderTraversal(root);
		}    
		               
        else if(secim==5){
	        printf("Hangi islemi yapmak istersiniz:\n1-Kok Silme\n2-Bir Sag Cocugu Olmayani Silme\n3-Bir Sol Cocugu Olmayani Silme\n4-Yapragi Silme\n5-Sag ve Sol Cocugu Olani Silme\n");
	        int sil;
	        scanf("%d",&sil);
	        if(sil==1){
	        	printf("Kok silindi.\n");
	        	int result = Kok(root);
	        	if (result != -1) {
        			printf("Agacin kok dugumu ogrenci numarasi: %d\n", result);
			    } else {
        			printf("Agacin kok dugumu bulunamadi.\n");
			    }
	        	root = deleteNode(root,result);
	        	inorderTraversal(root);
			}
			else if(sil==2){
				printf("Bir sag cocugu olmayan dugum (sol cocugu olan) silindi.\n");
				int result = SolCocuguOlan(root);
				if (result != -1) {
    				printf("Sadece sol cocugu olan dugumun ogrenci numarasi: %d\n", result);
    			} else {
        			printf("Sadece sol cocugu olan dugum bulunamadi.\n");
    			}
	        	root = deleteNode(root,result);
	        	inorderTraversal(root);
			}
			else if(sil==3){
				printf("Bir sol cocugu olmayan dugum (sag cocugu olan)silindi.\n");
				int result = SagCocuguOlan(root);
				if (result != -1) {
			        printf("Sadece sag cocugu olan dugumun ogrenci numarasi: %d\n", result);
			    } else {
			        printf("Sadece sag cocugu olan dugum bulunamadi.\n");
			    }
	        	root = deleteNode(root,result);
	        	inorderTraversal(root);
			}
			else if(sil==4){
				printf("Bir yaprak silindi.\n");
				int result  = Yaprak(root);
				if (result  != -1) {
        			printf("Agacin yaprak dugumunun ogrenci numarasi: %d\n", result);
    			} else {
        			printf("Agacin yaprak dugumu bulunamadi.\n");
    			}
	        	root = deleteNode(root,result);
	        	inorderTraversal(root);
			}
			else if(sil==5){
				int result  = SagveSolCocuguOlan(root);
				if (result  != -1) {
        			printf("Bulunan Dugumun Ogrenci Numarasi: %d\n", result);
    			} else {
    	    		printf("Hem sol hem de sag cocugu olan dugum bulunamadi.\n");
   				}
	        	root = deleteNode(root,result);
	        	inorderTraversal(root);
			}
		}         
         
		else if(secim==6){
			int istenilenOgrenciNo;
    		printf("\nBilgisi istenen dugumun ogrenci ogrenciNosini giriniz: ");
    		scanf("%d", &istenilenOgrenciNo);
    		
    		// Bilgisi istenen düðümden itibaren oluþan subtree üzerinde kaç adet düðüm olduðunu bulma
			int nodeCount = getNodeCount(root, istenilenOgrenciNo);
			printf("Bilgisi istenen dugumden itibaren olusan subtree'de %d adet dugum bulunmaktadir.\n", nodeCount);

		}     
		                
		else if(secim ==7){
			int istenilenOgrenciNo;
            printf("Ogrenci no:");
            scanf("%d", &istenilenOgrenciNo);
            Tree *targetNode = findNode(root, istenilenOgrenciNo);
            
            if (targetNode != NULL) {
                Tree *minNode = findMin(targetNode);
                Tree *maxNode = findMax(targetNode);
                
				printf("Bilgisi istenen dugumden itibaren olusan subtree'deki en kucuk dugum:\n");
                printf("Ogrenci No: %d, Isim: %s, Soyisim: %s, Yas: %d\n", minNode->ogrenciNo, minNode->isim, minNode->soyIsim, minNode->yas);
            
                printf("\nBilgisi istenen dugumden itibaren olusan subtree'deki en buyuk dugum:\n");
                printf("Ogrenci No: %d, Isim: %s, Soyisim: %s, Yas: %d\n", maxNode->ogrenciNo, maxNode->isim, maxNode->soyIsim, maxNode->yas);
            } 
            else{     		          
				printf("Bilgisi istenen dugum bulunamadi.\n");
            }
		}
        
		else if(secim==8){
		    printf("\nYapraklar yazdirildi:\n");
            printLeaves(root);	
		}        

        else if(secim==9){
        	printf("Cikis Yapildi.");
        	return 0;
		}
		else{
			printf("Yanlis bir secim yaptiniz!");
		}
    }   
    return 0;
}

// AVL aðacýný inorder olarak dolaþma
void inorderTraversal(struct Tree *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Ogrenci No: %d\t Isim: %s\tSoyisim: %s\tYas: %d\n", root->ogrenciNo, root->isim, root->soyIsim, root->yas);
        inorderTraversal(root->right);
    }
}

// AVL aðacýný preorder olarak dolaþma
void preorderTraversal(struct Tree *root) {
    if (root != NULL) {
        printf("Ogrenci No: %d\t Isim: %s\tSoyisim: %s\tYas: %d\n", root->ogrenciNo, root->isim, root->soyIsim, root->yas);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// AVL aðacýný postorder olarak dolaþma
void postorderTraversal(struct Tree *root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("Ogrenci No: %d\t Isim: %s\tSoyisim: %s\tYas: %d\n", root->ogrenciNo, root->isim, root->soyIsim, root->yas);
    }
}
struct Tree *sagaDondur(struct Tree *y) {
    struct Tree *x = y->left;
    struct Tree *T2 = x->right;

    // Dönüþ iþlemi
    x->right = y;
    y->left = T2;

    // Yükseklik güncellemeleri
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Tree *solaDondur(struct Tree *x) {
    struct Tree *y = x->right;
    struct Tree *T2 = y->left;

    // Dönüþ iþlemi
    y->left = x;
    x->right = T2;

    // Yükseklik güncellemeleri
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

struct Tree *newNode(int ogrenciNo, char isim[], char soyIsim[], int yas) {
	
    struct Tree *node = (struct Tree *)malloc(sizeof(struct Tree));

    node->ogrenciNo = ogrenciNo;
	snprintf(node->isim, sizeof(node->isim), "%s", isim);
    snprintf(node->soyIsim, sizeof(node->soyIsim), "%s", soyIsim);
    node->yas = yas;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

int max(int x, int y) {
    return (x > y) ? x : y;
}

int height(struct Tree *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int balanceGet(struct Tree *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// AVL aðacýna düðüm ekleme
struct Tree *insert(struct Tree *node, int ogrenciNo, char *isim, char *soyIsim, int yas) {
    // BST ekleme
    if (node == NULL) {
        return newNode(ogrenciNo, isim, soyIsim, yas);
    }
    
	// Benzer ogrenciNolý öðrenci kaydý varsa eklememe
    if (ogrenciNo == node->ogrenciNo) {
        printf("Ayni ogrenciNoli ogrenci kaydi mevcut. Eklenmedi.\n");
        return node;
    }

    if (ogrenciNo < node->ogrenciNo) {
    	node->left = insert(node->left, ogrenciNo, isim, soyIsim, yas);
    } 
	else 
        node->right = insert(node->right, ogrenciNo, isim, soyIsim, yas);

    // Yükseklik güncelleme
    node->height = 1 + max(height(node->left), height(node->right));

    // Denge faktörü al
    int balance = balanceGet(node);

    // Sol-Sol durumu
    if (balance > 1 && ogrenciNo < node->left->ogrenciNo) {
        return sagaDondur(node);
    }

    // Sað-Sað durumu
    if (balance < -1 && ogrenciNo > node->right->ogrenciNo) {
        return solaDondur(node);
    }

    // Sol-Sað durumu
    if (balance > 1 && ogrenciNo > node->left->ogrenciNo) {
        node->left = solaDondur(node->left);
        return sagaDondur(node);
    }

    // Sað-Sol durumu
    if (balance < -1 && ogrenciNo < node->right->ogrenciNo) {
        node->right = sagaDondur(node->right);
        return solaDondur(node);
    }

    return node;
}
struct Tree *deleteNode(struct Tree *root, int ogrenciNo) {
    if (root == NULL)
        return root;

    if (compareogrenciNos(ogrenciNo, root->ogrenciNo) == -1)
        root->left = deleteNode(root->left, ogrenciNo);
    else if (compareogrenciNos(ogrenciNo, root->ogrenciNo) == 1)
        root->right = deleteNode(root->right, ogrenciNo);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Tree *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            struct Tree *temp = minValueNode(root->right);

            root->ogrenciNo = temp->ogrenciNo;
            strcpy(root->isim, temp->isim);
            strcpy(root->soyIsim, temp->soyIsim);
            root->yas = temp->yas;

            root->right = deleteNode(root->right, temp->ogrenciNo);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = balanceGet(root);

    if (balance > 1 && balanceGet(root->left) >= 0)
        return sagaDondur(root);

    if (balance > 1 && balanceGet(root->left) < 0) {
        root->left = solaDondur(root->left);
        return sagaDondur(root);
    }

    if (balance < -1 && balanceGet(root->right) <= 0)
        return solaDondur(root);

    if (balance < -1 && balanceGet(root->right) > 0) {
        root->right = sagaDondur(root->right);
        return solaDondur(root);
    }

    return root;
}
int compareogrenciNos(int no1, int no2)
{
    if (no1 < no2)
        return -1;
    else if (no1 > no2)
        return 1;
    else
        return 0;
}

int Kok(Tree* root)
{
    if (root != NULL)
    {
        printf("%d %s %s %d\n", root->ogrenciNo, root->isim, root->soyIsim, root->yas);
        return root->ogrenciNo;
    }
    else
    {
        printf("Agac bos.\n");
        return -1;
	}
}
int SagCocuguOlan(struct Tree *root) {
	// Aðaç boþ veya sadece sað çocuðu olan düðüm bulunana kadar ilerle
    while (root != NULL && (root->left == NULL || root->right != NULL)) {
        // Sadece sað çocuðu olan düðümü bulduk
        if (root->left == NULL && root->right != NULL) {
            return root->ogrenciNo;
        }
		int leftt = SagCocuguOlan(root->left);
    	int rightt = SagCocuguOlan(root->right);

        // Eðer sað çocuk varsa, saða ilerle
        if (leftt!=-1) {
           return leftt;
        } else {
           return rightt;
        }
    }

    // Sadece sað çocuðu olan düðüm bulunamadýysa -1 döndür
    return -1;
}
int SolCocuguOlan(struct Tree *root) {
    // Aðaç boþ veya sadece sol çocuðu olan düðüm bulunana kadar ilerle
    while (root != NULL && (root->left != NULL || root->right == NULL)) {
        // Sadece sol çocuðu olan düðümü bulduk
        if (root->left != NULL && root->right == NULL) {
        	printf("%d %s %s %d\n", root->ogrenciNo, root->isim, root->soyIsim, root->yas);
            return root->ogrenciNo;
        }

        // Eðer sol çocuk varsa, sola ilerle
        if (root->left != NULL) {
            root = root->left;
        } else {
            // Sol çocuk yoksa ve sað çocuk da yoksa döngüden çýk
            break;
        }
    }

    // Sadece sol çocuðu olan düðüm bulunamadýysa -1 döndür
    return -1;
}
int Yaprak(struct Tree *root) {
    // Aðaç boþsa veya root yaprak düðüm ise root'un öðrenci numarasýný döndür
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return (root != NULL) ? root->ogrenciNo : -1;
    }

    // Aðaç üzerinde yaprak düðümü bulana kadar rekürsif olarak ara
    int leftLeaf = Yaprak(root->left);
    int rightLeaf = Yaprak(root->right);

    // Sol veya saðda yaprak düðüm bulunsa, öðrenci numarasýný döndür
    if (leftLeaf != -1) {
        return leftLeaf;
    } else if (rightLeaf != -1) {
        return rightLeaf;
    }

    // Yaprak düðüm bulunamazsa -1 döndür
    return -1;
}
int SagveSolCocuguOlan(struct Tree *root) {
    if (root == NULL) {
        return -1; // Bulunamazsa -1 döndür
    }

    // Eðer hem sol hem de sað çocuklarý varsa, bu düðümün deðerini döndür
    if (root->left != NULL && root->right != NULL) {
        return root->ogrenciNo;
    }

    // Sol alt aðacý kontrol et
    int leftResult = SagveSolCocuguOlan(root->left);
    if (leftResult != -1) {
        return leftResult;
    }

    // Sað alt aðacý kontrol et
    return SagveSolCocuguOlan(root->right);
}
struct Tree *minValueNode(struct Tree *root)
{
	struct Tree *current = root;
	
    // En küçük deðere sahip düðüm, sol alt aðaçtaki en soldaki düðümdür
    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}
// Bilgisi istenen düðümden itibaren oluþan subtree üzerinde kaç adet düðüm olduðunu bulan fonksiyon
int getNodeCountFromNode(struct Tree *node) {
    // Bilgisi istenen düðümden itibaren oluþan subtree üzerindeki düðüm sayýsýný hesapla
    if (node == NULL) {
        return 0;
    }

    return 1 + getNodeCountFromNode(node->left) + getNodeCountFromNode(node->right);
}

// Bilgisi istenen düðümden itibaren oluþan subtree üzerinde kaç adet düðüm olduðunu bulan fonksiyon
int getNodeCount(struct Tree *root, int istenenOgrenciNo) {
    // Bilgisi istenen düðümü bul
    struct Tree *targetNode = findNode(root, istenenOgrenciNo);

    // Bilgisi istenen düðüm bulunamazsa veya aðaç boþsa, 0 döndür
    if (targetNode == NULL) {
        return 0;
    }

    // Bilgisi istenen düðümden itibaren oluþan subtree üzerindeki düðüm sayýsýný hesapla
    return getNodeCountFromNode(targetNode);
}

// Bilgisi istenen düðümü bulan fonksiyon
Tree *findNode(Tree *root, int ogrenciNo) {
    if (root == NULL || root->ogrenciNo == ogrenciNo) {
        return root;
    }

    if (ogrenciNo < root->ogrenciNo) {
        return findNode(root->left, ogrenciNo);
    }

    return findNode(root->right, ogrenciNo);
}

// Bilgisi istenen düðümden itibaren oluþan subtree'deki en küçük düðümü bulan fonksiyon
Tree *findMin(Tree *root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root;
}

// Bilgisi istenen düðümden itibaren oluþan subtree'deki en büyük düðümü bulan fonksiyon
Tree *findMax(Tree *root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->right != NULL) {
        root = root->right;
    }

    return root;
}

// Aðacýn son þeklinde sadece yapraklarý ekrana yazma
void printLeaves(struct Tree *root) {
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) {
        	printf("Yaprak -> Ogrenci No: %d\t Isim: %s\tSoyisim: %s\tYas: %d\n", root->ogrenciNo, root->isim, root->soyIsim, root->yas);
        }
        printLeaves(root->left);
        printLeaves(root->right);
    }
}
