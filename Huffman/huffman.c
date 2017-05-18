#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct Node Node;
struct Node
{
    char value;
    int frequencia;
    Node* parent;
    Node* left;
    Node* right;
};

typedef struct ListaDENode ListaDENode;
struct ListaDENode
{
    Node * no;
    struct ListaDENode * next;
    struct ListaDENode * prev;
};



int getByteFrequency(FILE* arq, struct Node **root);
void inOrder(struct Node *root);
int AddNode(Node **root, char value, int tiposDeCaracteres);

void treeToList_L(Node* n, ListaDENode** head, ListaDENode** tail);
void walkTree_L(struct Node *root, ListaDENode ** head, ListaDENode** tail);
void InsertionSort_L(struct ListaDENode *node);
void inOrderList_L(ListaDENode *root);
Node * BuildHuffmanTree(ListaDENode* lista, Node* arvore);

int qtdNode(Node * arvore, int qtdNodeA);
int qtdNodeTree(Node *arvore);
void invertTable(unsigned char ** table, int numNodeTree, int typeNodeTree);
int achaFolha(unsigned char ** table, Node * arvore, int posFolha, int numNodeTree);
unsigned char ** tableTree(Node * arvore, int numNodeTree, int typeNodeTree);
unsigned char * divideTableVector(unsigned char ** table, int numNodeTree, int typeNodeTree);
void tabelaToTree(unsigned char ** table, Node ** huffmanTree, int numNodeTree, int typeNodeTree);
void convertCode(FILE * arquivoDescomprimido, unsigned char ** tabela, char *nomeArquivoComprimido, int qtdTiposCaracter, int numNodeTree);
void CompressFile(char * nomeArquivoDescomprimido, char nomeArquivoComprimido[]);
void DescompressFile(char ArquivoDescomprimido[], char ArquivoComprimido[]);

void FreeHuffmanTree(Node ** arvore);
void FreeListValue(ListaDENode ** lista);
void FreeTableBytes(unsigned char *** tabela, int qtdTiposCaracter);

char bintoASCII(char binario[8]);
void ascIItoBin(unsigned char let, char bin[8]);
int imprimeBIN(char t[9]);
char * toStringBin(char t[9]);

int main(int argc, char *args[])
{
    if(argc != 4)
    {
printf("%d",argc);
        printf("\nParametros invalidos\n");
        exit(1);
    }
    else
    {
        if(strcmp(args[1], "-c")==0)
        {
				CompressFile(args[2], args[3]);
        }
        else
        {
            if(strcmp(args[1], "-x")==0)
            {
                 DescompressFile(args[3],args[2]);
            }
            else
            {
                printf("\nParametros invalidos\n");
                exit(1);
            }
        }
    }
    return EXIT_SUCCESS;
}


void inOrder(struct Node *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
       printf("Valor: %c :: Frequencia: %d\n",root->value,root->frequencia);
        inOrder(root->right);
    }
}
int getByteFrequency(FILE* arq, struct Node **root)
{
    int tiposDeCaracteres = 0;
    unsigned char c;
    while(!feof(arq))
    {
        fscanf(arq, "%c", &c);
        if(!feof(arq))
            tiposDeCaracteres = AddNode(root, c, tiposDeCaracteres);
    }
    return tiposDeCaracteres;
}

int AddNode(Node** root, char value, int tiposDeCaracteres)
{
    if((*root) == NULL)
    {
        (*root) = (Node*)malloc(sizeof(Node));
        (*root)->left = NULL;
        (*root)->right = NULL;
        (*root)->value = value;
        (*root)->frequencia = 1;
        tiposDeCaracteres++;
    }

    else
    {
        if(value==(*root)-> value)
            (*root)->frequencia++;
        else
        {
            if(value>(*root)->value)
                tiposDeCaracteres = AddNode(&(*root)->right,value, tiposDeCaracteres);
            else
                tiposDeCaracteres = AddNode(&(*root)->left,value, tiposDeCaracteres);
        }
    }
    return tiposDeCaracteres;
}
void treeToList_L(Node* n, ListaDENode** head, ListaDENode** tail)
{
    if((*head) == NULL)
    {
        (*head) = (ListaDENode*)malloc(sizeof(ListaDENode));
        (*head)->no = (Node*)malloc(sizeof(Node));
        (*head)->no->frequencia = n->frequencia;
        (*head)->no->value = n->value;
        (*head)->no->left = NULL;
        (*head)->no->right = NULL;
        (*head)->no->parent = NULL;
        (*head)->prev = NULL;
        (*head)->next = NULL;
        *tail = *head;
    }
    else
    {
        ListaDENode* temp=NULL;
        temp = (ListaDENode*)malloc(sizeof(ListaDENode));
        temp->no = (Node*)malloc(sizeof(Node));
        temp->no->value = n->value;
        temp->no->frequencia = n->frequencia;
        temp->no->left = NULL;
        temp->no->right = NULL;
        temp->no->parent = NULL;
        temp->prev = (*tail);
        temp->next = NULL;
        (*tail)->next=temp;
        (*tail) = temp;
    }
}

void walkTree_L(struct Node *root, ListaDENode ** head, ListaDENode** tail)
{
    if(root != NULL)
    {
        walkTree_L(root->left,head,tail);
        treeToList_L(root,head,tail);
        walkTree_L(root->right,head,tail);
    }
}

void InsertionSort_L(ListaDENode* node)
{
    ListaDENode *aux1=NULL, *aux2=NULL, *temp = NULL;
    Node* eleito=NULL;

    for(aux1 = node->next ; aux1!=NULL ; aux1=aux1->next)
    {
        eleito = aux1->no;
        aux2 = aux1->prev;
        temp = aux2;
        while((aux2!=NULL) && (eleito->frequencia < aux2->no->frequencia))
        {
            aux2->next->no = aux2->no;
            temp = aux2;
            aux2 = aux2->prev;
        }
        if(aux2 != NULL)
        {
            aux2->next->no = eleito;
        }
        else
        {
            temp->no = eleito;
        }
    }
}
void inOrderList_L(ListaDENode *root)
{
    if(root != NULL)
    {
        printf("Valor: %c :: Frequencia: %d\n",root->no->value,root->no->frequencia);
        inOrderList_L(root->next);
    }
}

Node * BuildHuffmanTree(ListaDENode* lista, Node* arvore)
{
    Node * menor1 = NULL;
    Node * menor2 = NULL;
    Node * temp = NULL;
    InsertionSort_L(lista);
   while(lista->next != NULL)
    {
        menor1 = lista->no;
        menor2 = lista->next->no;
        lista = lista->next;
        temp = (Node*)malloc(sizeof(Node));
        temp->left = menor1;
        menor1->parent = temp;
        temp->right = menor2;
        menor2->parent = temp;
        temp->value = 0;
        temp->frequencia = menor1->frequencia + menor2->frequencia;
        lista->no = temp;
         InsertionSort_L(lista);
        }
    lista->no->parent == NULL;
    return lista->no;
}

int qtdNode(Node * arvore, int qtdNodeA)
{
    if(arvore != NULL)
    {
        qtdNodeA = qtdNode(arvore->left, qtdNodeA);
        qtdNodeA = qtdNode(arvore->right, qtdNodeA);
        qtdNodeA++;
    }
    return qtdNodeA;
}

int qtdNodeTree(Node *arvore)
{
    int qtdNodeA = 0;
    return qtdNode(arvore, qtdNodeA);
}

int achaFolha(unsigned char ** table, Node * arvore, int posFolha, int numNodeTree)
{
    if(arvore != NULL)
    {
        posFolha = achaFolha(table, arvore->left, posFolha, numNodeTree);
        posFolha = achaFolha(table, arvore->right, posFolha, numNodeTree);
        if(arvore->left == NULL && arvore->right == NULL)
        {
            int j;
            table[posFolha] = (unsigned char*)malloc(sizeof(unsigned char)*(numNodeTree+2));
            int k;
            for(k = 0; k< numNodeTree+2; k++)
            {
                table[posFolha][k] = '\0';
            }

            for(j = 0; j < numNodeTree+2; j++)
            {
                if(arvore != NULL)
                {
                    if(j == 0)
                    {
                        table[posFolha][j] = arvore->value;
                    }
                    else
                    {
                        if(j == numNodeTree+2 - 1)
                        {
                            table[posFolha][j] = '\0';
                        }
                        else
                        {
                            if(arvore->parent!=NULL)  {
                                if(arvore->parent != NULL && arvore == arvore->parent->left)
                                {
                                     table[posFolha][j] = '0';
                                    arvore = arvore->parent;
                                }
                                else
                                {
                                    if(arvore->parent->right != NULL && arvore == arvore->parent->right)
                                    {
                                         table[posFolha][j] = '1';
                                        arvore = arvore->parent;
                                    }
                                }
                            }
                            else
                            {
                                table[posFolha][j] = '\0';
                                break;
                            }
                        }
                    }
                }
            }
            posFolha++;
			}
    }
    return posFolha;
}

void invertTable(unsigned char ** table, int numNodeTree, int typeNodeTree)
{
    unsigned char * temp = (unsigned char*)malloc(sizeof(unsigned char)*numNodeTree);
    int i, j = 1, cont = 0;
    for(i=0; i<typeNodeTree; i++)
    {
        while(table[i][j] != '\0')
        {
            temp[j-1] = table[i][j];
            j++;
            cont++;
        }
        for(j = cont-1; j>=0; j--)
        {
            table[i][cont-j] = temp[j];
        }
        j = 1;
        cont = 0;
    }
    free(temp);
}

unsigned char ** tableTree(Node * arvore, int numNodeTree, int typeNodeTree)
{
    int test=0;
    unsigned char ** table = (unsigned char**)malloc(sizeof(unsigned char*)*typeNodeTree);
	test = achaFolha(table, arvore, 0, numNodeTree);
    
    invertTable(table, numNodeTree, typeNodeTree);
    return table;
}

unsigned char * divideTableVector(unsigned char ** table, int numNodeTree, int typeNodeTree)
{
    unsigned char * Vector = (char*)malloc(sizeof(char)*typeNodeTree);
    unsigned char * temp = (char*)malloc(sizeof(char)*numNodeTree+3);
    int i, j;
    for(i = 0; i < typeNodeTree; i++)
    {
        Vector[i] = table[i][0];
        j = 1;
        while((table[i][j-1] != '\0') || (j-1 == 0))
        {
            temp[j-1] = table[i][j];
            j++;
        }
        j = 0;
        do
        {
            table[i][j] = temp[j];
            j++;
        }
        while(temp[j-1] != '\0');
    }
    free(temp);
    return Vector;
}

void tabelaToTree(unsigned char ** table, Node ** huffmanTree, int numNodeTree, int typeNodeTree)
{
    int i, j;
    Node * nodeTemp = (*huffmanTree);
    nodeTemp = (Node*)malloc(sizeof(Node));
    nodeTemp->value = 0;
    nodeTemp->frequencia = 0;
    nodeTemp->left = NULL;
    nodeTemp->right = NULL;
    nodeTemp->parent = NULL;
    (*huffmanTree) = nodeTemp;


    for(i = 0; i < typeNodeTree; i++)
    {

        for(j = 1; (j < numNodeTree-1) && (table[i][j] != '\0'); j++)
        {

            if(table[i][j] == '1')
            {
                if(nodeTemp->right == NULL)
                {
                    nodeTemp->right = (Node*)malloc(sizeof(Node));
                    nodeTemp->right->value = 0;
                    nodeTemp->right->frequencia = 0;
                    nodeTemp->right->left = NULL;
                    nodeTemp->right->right = NULL;
                    nodeTemp->right->parent = nodeTemp;
                }
                nodeTemp = nodeTemp->right;
            }
            else
            {
                if(table[i][j] == '0')
                {
                    if(nodeTemp->left == NULL)
                    {
                        nodeTemp->left = (Node*)malloc(sizeof(Node));
                        nodeTemp->left->value = 0;
                        nodeTemp->left->frequencia = 0;
                        nodeTemp->left->left = NULL;
                        nodeTemp->left->right = NULL;
                        nodeTemp->left->parent = nodeTemp;
                    }
                    nodeTemp = nodeTemp->left;
                }
            }
        }
        nodeTemp->value = table[i][0];
        nodeTemp = (*huffmanTree);
    }
}

void convertCode(FILE * arquivoDescomprimido, unsigned char ** tabela, char *nomeArquivoComprimido, int qtdTiposCaracter, int numNodeTree)
{
    int i = 0, j = 0;
	int contCaracterNome = 0;
	for(i = 0; nomeArquivoComprimido[i] != '\0'; i++){
		contCaracterNome++;
	}
	char * novoNome = (char*)malloc(sizeof(char)*(contCaracterNome+5));
	strcpy(novoNome, nomeArquivoComprimido);
    strcat(novoNome, ".hx");
	
	FILE * arquivoComprimido = NULL;
	
    if((arquivoComprimido = fopen(novoNome, "w+b")) == NULL)
    {
        printf("\nNao foi possivel criar o arquivo %s", novoNome);
    }
	free(novoNome);
    
	fseek(arquivoComprimido, 0, SEEK_SET);
    fprintf(arquivoComprimido, "%d", qtdTiposCaracter);
    fprintf(arquivoComprimido,"%c",'\0');
    fprintf(arquivoComprimido, "%d", numNodeTree);
    fprintf(arquivoComprimido,"%c",'\0');

    for(i = 0; i < qtdTiposCaracter; i++)
    {
        for(j = 0; j==0 || tabela[i][j] != '\0'; j++)
        {
            fprintf(arquivoComprimido, "%c", tabela[i][j]);
        }

        fprintf(arquivoComprimido, "%c", tabela[i][j]);
    }

    unsigned char c;
    char binario[8];
    int contBin = 0;
    unsigned char gravaArquivo; 
    fseek(arquivoDescomprimido, 0, SEEK_SET);
    while(!feof(arquivoDescomprimido))
    {
        fscanf(arquivoDescomprimido, "%c", &c);
        if(!feof(arquivoDescomprimido))
		{
            for(i = 0; i < qtdTiposCaracter; i++)
            {
                if(tabela[i][0] == c)
                {
                    j = 1;
                    while(tabela[i][j] != '\0') 
                    {
                        if(contBin < 8) 
                        {
                            binario[contBin] = tabela[i][j];
                            contBin++;
                            j++;
                        }
                        else
                        {
                            gravaArquivo = bintoASCII(binario);
                            fprintf(arquivoComprimido, "%c", gravaArquivo);
                            contBin = 0;
                        }
                    }
                    break;
                }
            }
        }
    }
   
    if(contBin != 0)
    {
        for(i = contBin; i < 8; i++)
        {
            binario[i] = 0;
        }
        gravaArquivo = bintoASCII(binario);
        fprintf(arquivoComprimido, "%c", gravaArquivo);
    }
    
    fprintf(arquivoComprimido, "%d", 8-contBin);
    fclose(arquivoComprimido);
}

void CompressFile(char * nomeArquivoDescomprimido, char nomeArquivoComprimido[])
{
   
    ListaDENode * listaDeBytes = NULL;
    ListaDENode * tail = NULL;
    Node * root = NULL;
    Node * treeHuffman = NULL;
    FILE * arquivoDescomprimido = NULL;
    int TiposCaracter = 0;
    unsigned char ** tabela = NULL;
    int numNodeTree = 0;

    
    if((arquivoDescomprimido = fopen(nomeArquivoDescomprimido, "rb")) == NULL)
    {
        printf("\nErro ao abrir arquivo %s", nomeArquivoDescomprimido);
        exit(1);
    }
	printf("\nAguarde, o arquivo esta sendo processado.");
    TiposCaracter = getByteFrequency(arquivoDescomprimido,&root);
    fclose(arquivoDescomprimido);
    walkTree_L(root, &listaDeBytes, &tail);
    
	printf("\nCriando arvore!");
    treeHuffman = BuildHuffmanTree(listaDeBytes, treeHuffman);
    treeHuffman->parent = NULL;

    numNodeTree = qtdNodeTree(treeHuffman);
    tabela = tableTree(treeHuffman, numNodeTree, TiposCaracter);

    if((arquivoDescomprimido = fopen(nomeArquivoDescomprimido, "rb")) == NULL)
    {
        printf("\nErro ao abrir arquivo %s", nomeArquivoDescomprimido);
        exit(1);
    }
	printf("\nEstamos, Comprimindo o arquivo!\n");
    convertCode(arquivoDescomprimido, tabela, nomeArquivoComprimido, TiposCaracter, numNodeTree);
	printf("Arquivo comprimido!\n");
    fclose(arquivoDescomprimido);
	inOrder(root);
	
	FreeHuffmanTree(&root);

	FreeListValue(&listaDeBytes);

	free(tail);

	FreeTableBytes(&tabela, TiposCaracter);

}
void DescompressFile(char ArquivoDescomprimido[], char ArquivoComprimido[])
{
    FILE* arqComprimido=NULL;
    FILE* arqDescomprimido = NULL;
    int qtdTiposCaracter,i,j,padding=200;
    unsigned char **tabela;
    unsigned char c;
    int numNodeTree;

    printf("\nArquivoComprimido: %s",ArquivoComprimido);

    arqComprimido = fopen(ArquivoComprimido,"r+b");
    if(arqComprimido == NULL){
        printf("\nNao foi possivel abrir o arquivo %s",ArquivoComprimido);
        exit(1);
    }
    fseek(arqComprimido,-sizeof(char),SEEK_END);
    fscanf(arqComprimido,"%d",&padding);
    fseek(arqComprimido,0,SEEK_SET);


    fscanf(arqComprimido,"%d",&qtdTiposCaracter);
    fseek(arqComprimido,sizeof(char),1);
    fscanf(arqComprimido,"%d",&numNodeTree);
    fseek(arqComprimido,sizeof(char),1);

    
    tabela = (unsigned char**)malloc(sizeof(unsigned char*)*qtdTiposCaracter);

    for(i = 0;i<qtdTiposCaracter;i++)
        tabela[i] = (unsigned char*)malloc(sizeof(unsigned char)*numNodeTree);

    for(i=0;i<qtdTiposCaracter;i++){
        for(j=0;j<numNodeTree;j++){
            fscanf(arqComprimido,"%c", &c);

            if(j != 0 && c == '\0'){
                tabela[i][j] = c;
                if(j<numNodeTree-1)
                fseek(arqComprimido, -sizeof(unsigned char), SEEK_CUR);
            }
            else{
                tabela[i][j] = c;
            }
        }
    }


        Node* huffmanTree = NULL;
        tabelaToTree(tabela, &huffmanTree,numNodeTree,qtdTiposCaracter);


        printf("\nIniciando leitura do arquivo comprimido\n");

        arqDescomprimido = fopen(ArquivoDescomprimido,"w+b");
        char bin[8];
        Node* temp=NULL;
        temp = huffmanTree;
		int test = 0;
		int cont = -1;
		unsigned char gambiarra;
    while(!feof(arqComprimido))
    {

        fscanf(arqComprimido,"%c",&c);

		fscanf(arqComprimido, "%c", &gambiarra);
		if(!feof(arqComprimido)){
			fscanf(arqComprimido, "%c", &gambiarra);
			if(feof(arqComprimido)){
				cont = padding;
			}
			fseek(arqComprimido,-sizeof(char),1);
			fseek(arqComprimido,-sizeof(char),1);

			ascIItoBin(c,bin);

			for(i=0; i<8-cont; i++)
			{
				if(bin[i] == 1)
				{
					temp = temp->right;
				}

				if(bin[i] == 0)
				{
					temp = temp->left;
				}
				if(temp->left == NULL && temp->right == NULL)
				{
					fprintf(arqDescomprimido,"%c",temp->value);
					temp = huffmanTree;
				}
			}
			if(cont == padding){
				break;
			}
		}
		else{
			break;
		}
    }
printf("\nArquivo foi descomprimido check a pasta do execultavel!\n");


	FreeHuffmanTree(&huffmanTree);
	FreeTableBytes(&tabela, qtdTiposCaracter);
}

void FreeHuffmanTree(Node ** arvore){
	if((*arvore) != NULL){
		FreeHuffmanTree(&((*arvore)->left));
		FreeHuffmanTree(&((*arvore)->right));
		free((*arvore));
	}
}

void FreeListValue(ListaDENode ** lista){
	if((*lista) != NULL){
		FreeListValue(&((*lista)->next));
		free((*lista));
	}
}

void FreeTableBytes(unsigned char *** tabela, int qtdTiposCaracter){
	int i = 0, j = 0; 
	unsigned char ** test = (*tabela);
	for(i = 0; i < qtdTiposCaracter; i++){
		free(test[i]);
	}
	free(test);
}



char bintoASCII(char binario[8])
{
    int i;
    unsigned char value = 0;
    for(i = 0; i < 8; i++)
    {
        if(binario[i] == '1')
            value += pow(2, 7-i);
    }
    return value;
}

void ascIItoBin(unsigned char let, char bin[8])
{
    int i;
    int j;
    for(i = 0; i<8; i++)
    {

        bin[7-i] = let%2;
        let = let / 2;
    }
}

int imprimeBIN(char t[9])
{
    int i = 0;
    int imprime = 0;
    for(i = 0; i < 8; i++)
    {
        imprime += t[7-i]*pow(10, i);
    }
    return imprime;
}

char * toStringBin(char t[9])
{
    int i = 0;
    char * imprime = (char*)malloc(9*sizeof(char));
    for(i = 0; i < 8; i++)
    {
        if(t[i] == 1)
            t[i] = '1';
        else
            t[i] = '0';
    }
    t[8] ='\0';
    return imprime;
}
