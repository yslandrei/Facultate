use case

create table proprietari(
	id int primary key identity,
	nume varchar(50),
	prenume varchar(50),
	gen varchar(50),
	functie varchar(50)
);

create table chiriasi(
	id int primary key identity,
	nume varchar(50),
	prenume varchar(50),
	gen varchar(50),
	data_nastere date,
	id_proprietar int,
	constraint fk_id_proprietar foreign key (id_proprietar) references proprietari(id)
);

create table casa(
	id int primary key identity,
	numar int,
	localitate varchar(50),
	cod_postal varchar(50),
	id_proprietar int,
	constraint fk_id_proprietar1 foreign key (id_proprietar) references proprietari(id)
);

create table piese_mobilier(
	id int primary key identity,
	denumire varchar(50),
	descriere varchar(50),
	cantitate int,
	pret int
);

create table achizitie(
	 id_mobilier int,
	 id_casa int,
	 constraint pk_achizitie primary key (id_mobilier, id_casa),
	 constraint fk_id_mobilier foreign key (id_mobilier) references piese_mobilier(id),
	 constraint fk_id_casa foreign key (id_casa) references casa(id),
	 trimitere date,
	 ridicare date

);

go
create or alter procedure pula
@id_ap int,
@id_mobtrap int,
@trim date,
@rid date
as
begin
	if exists(select * from achizitie where achizitie.id_casa=@id_ap and achizitie.id_mobilier=@id_mobtrap)
	begin
		update achizitie set trimitere=@trim, ridicare=@rid where id_casa=@id_ap and id_mobilier=@id_mobtrap
	end
	else
	begin
		insert into achizitie (id_mobilier, id_casa, trimitere, ridicare)
		values (@id_mobtrap, @id_ap, @trim, @rid)
	end
end

go
create view pulaaa as
select piese_mobilier.denumire, count(piese_mobilier.denumire) as numar_de_mobile
from achizitie join piese_mobilier on achizitie.id_mobilier=piese_mobilier.id
group by piese_mobilier.denumire
having count(piese_mobilier.denumire)<=3