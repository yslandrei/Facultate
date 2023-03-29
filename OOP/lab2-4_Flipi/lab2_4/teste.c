#include <stdio.h>
#include "domain.h"
#include "repository.h"
#include "validare.h"
#include "service.h"
#include <assert.h>
#include <string.h>


void teste_domain()
{
	//teste create
	Masina* masina = creaza_masina("HR24FLP", "golf", "mini");
	assert(strcmp((*masina).nr_inmatriculare, "HR24FLP") == 0);
	assert(strcmp((*masina).model, "golf") == 0);
	assert(strcmp((*masina).categorie, "mini") == 0);
	
	//teste copy
	Masina* copy_masina = copiaza_masina(masina);
	assert(strcmp((*masina).nr_inmatriculare, (*copy_masina).nr_inmatriculare) == 0);
	assert(strcmp((*masina).model, (*copy_masina).model) == 0);
	assert(strcmp((*masina).categorie, (*copy_masina).categorie) == 0);

	distruge_masina(copy_masina);
	
	//teste modifica
	
	Masina* masina_noua = creaza_masina("HR24FLP", "passat", "sedan");
	modifica_masina(masina, masina_noua);
	assert(strcmp((*masina).categorie, "sedan") == 0);
	assert(strcmp((*masina).model, "passat") == 0);
	
	distruge_masina(masina_noua);
}

void teste_repository()
{
	//teste creare
	Lista* lista = creaza_lista();
	assert(size(lista) == 0);

	//teste adaugare + resize
	Masina* masina1 = creaza_masina("HR24FLP", "golf", "mini");
	Masina* masina2 = creaza_masina("HR01RSU", "kango", "suv");
	Masina* masina3 = creaza_masina("HR01JRR", "kuga", "suv");
	Masina* masina4 = creaza_masina("HR78CLS", "audi", "sport");
	
	adauga_masina(lista, masina1);
	adauga_masina(lista, masina2);
	adauga_masina(lista, masina3);
	assert(size(lista) == 3);

	//teste cautare + setare
	Masina* masina_cautata = get(lista, 0);
	assert(strcmp((*masina_cautata).nr_inmatriculare, "HR24FLP") == 0);
	assert(strcmp((*masina_cautata).model, "golf") == 0);
	assert(strcmp((*masina_cautata).categorie, "mini") == 0);
	assert((*masina_cautata).inchiriere == 0);
	
	seteaza_element(lista, 1, masina4);
	masina_cautata = get(lista, 1);
	
	assert(strcmp((*masina_cautata).nr_inmatriculare, "HR78CLS") == 0);
	assert(strcmp((*masina_cautata).model, "audi") == 0);
	assert(strcmp((*masina_cautata).categorie, "sport") == 0);

	//teste copiere
	
	Lista* copie_lista = copy_list(lista);
	assert(size(copie_lista) == 3);

	masina_cautata = get(copie_lista, 0);
	assert(strcmp((*masina_cautata).nr_inmatriculare, "HR24FLP") == 0);
	assert(strcmp((*masina_cautata).model, "golf") == 0);
	assert(strcmp((*masina_cautata).categorie, "mini") == 0);
	assert((*masina_cautata).inchiriere == 0);
	
	distruge_lista(copie_lista);
	distruge_lista(lista);
}

void teste_validare()
{
	//teste validare
	Masina* masina1 = creaza_masina("HR24FLP", "golf", "mini");
	assert(validare(masina1) == 1);

	Masina* masina2 = creaza_masina("HR01RSUU", "kango", "suv");
	assert(validare(masina2) == 0);

	Masina* masina3 = creaza_masina("HR01JRR", "", "suv");
	assert(validare(masina3) == 0);

	Masina* masina4 = creaza_masina("HR78CLS", "audi", "s");
	assert(validare(masina4) == 0);

	distruge_masina(masina1);
	distruge_masina(masina2);
	distruge_masina(masina3);
	distruge_masina(masina4);
}

void teste_service()
{
	//teste adaugare
	Lista* lista = creaza_lista();

	int adaugare_gresit1 = serv_adauga(lista, "HR24FLPP", "golf", "mini");
	assert(adaugare_gresit1 == 0);

	int adaugare_gresit2 = serv_adauga(lista, "HR24FLP", "", "suv");
	assert(adaugare_gresit2 == 0);

	int adaugare_corect = serv_adauga(lista, "HR24FLP", "golf", "mini");
	assert(adaugare_corect == 1);
	assert(size(lista) == 1);

	//teste cautare
	
	int pozitie = cauta_id(lista, "HR24FLP");
	assert(pozitie == 0);

	int pozitie_gresit = cauta_id(lista, "HR01RSU");
	assert(pozitie_gresit == -1);
	
	//teste modificare
	int modificat = serv_modifica(lista, "HR24FLP", "passat", "sedan");
	assert(modificat == 1);
	assert(strcmp((*(Masina*)(lista)->elemente[0]).model, "passat") == 0);
	int modificat_gresit = serv_modifica(lista, "HR01RSU", "kango", "suv");
	assert(modificat_gresit == 0);
	
	//teste status inchiriere

	int succes1 = serv_inchiriaza(lista, "HR24FLP");
	assert((*(Masina*)lista->elemente[0]).inchiriere == 1);
	assert(succes1 == 1);

	int fail1 = serv_inchiriaza(lista, "HR01FLP");
	assert(fail1 == 0);

	int succes2 = serv_returnare(lista, "HR24FLP");
	assert((*(Masina*)lista->elemente[0]).inchiriere == 0);
	assert(succes2 == 1);

	int fail2 = serv_returnare(lista, "HR01FLP");
	assert(fail2 == 0);
	
	//teste filtrare
	Masina* masina1 = creaza_masina("HR01RSU", "kango", "suv");
	Masina* masina2 = creaza_masina("HR01JRR", "kuga", "suv");
	Masina* masina3 = creaza_masina("HR78CLS", "audi", "suv");
	adauga_masina(lista, masina1);
	adauga_masina(lista, masina2);
	adauga_masina(lista, masina3);

	
	Lista* filtered_list;
	filtered_list = serv_filtrare_categorie(lista, "sport");
	assert(size(filtered_list) == 0);
	distruge_lista(filtered_list);

	filtered_list = serv_filtrare_categorie(lista, "suv");
	assert(size(filtered_list) == 3);
	distruge_lista(filtered_list);

	filtered_list = serv_filtrare_judet(lista, "HR");
	assert(size(filtered_list) == 4);
	distruge_lista(filtered_list);

	//teste sortare
	serv_sortare_model(lista);
	assert(strcmp((*(Masina*)lista->elemente[0]).model , "audi") == 0);

	serv_sortare_categorie(lista);
	assert(strcmp((*(Masina*)lista->elemente[0]).categorie, "sedan") == 0);
	

	distruge_lista(lista);
}

void teste_lista_de_liste()
{
	Lista* undo_list = creaza_lista();

	Lista* lista = creaza_lista();
	
	adauga_pas_undo(undo_list, lista);

	adauga_masina(lista, creaza_masina("HR01RSU", "kango", "suv"));
	adauga_pas_undo(undo_list, lista);

	adauga_masina(lista, creaza_masina("VL24ZRE", "golf", "mini"));
	assert(size(undo_list) == 2);

	lista = executa_pas_undo(undo_list, lista);
	assert(size(undo_list) == 1);
	assert(size(lista) == 1);
	assert(strcmp((*(Masina*)lista->elemente[0]).nr_inmatriculare, "HR01RSU") == 0);

	lista = executa_pas_undo(undo_list, lista);
	assert(size(lista) == 0);

	distruge_lista(undo_list);
	distruge_lista(lista);
}

void run_tests()
{
	teste_domain();
	teste_repository();
	teste_validare();
	teste_service();
	teste_lista_de_liste();
	printf("Testele au fost rulate cu succes!");
}