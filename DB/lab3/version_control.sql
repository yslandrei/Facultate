create procedure do_v1 as
begin
alter table employee
alter column salary int NOT NULL
UPDATE version_control SET v = 1
print 'coloana salary din tabelul employee are acum tipul de date INT'
end

create procedure undo_v1 as
begin
alter table employee
alter column salary money NOT NULL
UPDATE version_control SET v = 0
print 'coloana salary din tabelul employee are acum tipul de date MONEY'
end


create procedure do_v2 as 
begin
alter table employee add constraint df_employee_salary default 2080 for salary
UPDATE version_control SET v = 2
print 'coloana salary din tabelul employee are acum ca valoare implicita 2080'
end

create procedure undo_v2 as 
begin
alter table employee 
drop constraint df_employee_salary
UPDATE version_control SET v = 1
print 'coloana salary din tabelul employee nu mai are acum ca valoare implicita 2080'
end


create procedure do_v3 as
begin
create table volunteer (
	id bigint identity,
	name varchar(50) not null,
	address_id bigint foreign key references address(id)
)
UPDATE version_control SET v = 3
print 'tabelul volunteer a fost creat'
end

create procedure undo_v3 as
begin
drop table volunteer
UPDATE version_control SET v = 2
print 'tabelul volunteer a fost sters'
end


create procedure do_v4 as
begin
alter table volunteer
add hours_per_day bigint not null
UPDATE version_control SET v = 4
print 'coloana hours_per_dar din tabelul volunteer a fost creata'
end

create procedure undo_v4 as
begin
alter table volunteer
drop column hours_per_day
UPDATE version_control SET v = 3
print 'coloana hours_per_dar din tabelul volunteer a fost stearsa'
end


create procedure do_v5 as
begin
alter table volunteer
add constraint fk_volunteer_address_id foreign key(addres_id) references address(id)
UPDATE version_control SET v = 5
print 'constraintul din tabela volunteer foreign pentru address_id a fost adaugat'
end

create procedure undo_v5 as
begin
alter table volunteer
drop constraint fk_volunteer_address_id
UPDATE version_control SET v = 4
print 'constraintul din tabela volunteer foreign pentru address_id a fost stearsa'
end



CREATE PROCEDURE main @vers INT
AS
BEGIN
    DECLARE @myVers INT;
    DECLARE @sql NVARCHAR(100);

    SELECT @myVers = v FROM version_control;

    IF @vers > 5
    BEGIN
        PRINT 'Eroare: versiune inexistenta';
    END
    ELSE IF @vers < 0
    BEGIN
        PRINT 'Eroare: versiune mai mica ca 0';
    END
    ELSE IF @vers > @myVers
    BEGIN
        WHILE @vers > @myVers
        BEGIN
            SET @myVers = @myVers + 1;
            SET @sql = N'EXEC do_v' + CAST(@myVers AS NVARCHAR(10));
            EXEC sp_executesql @sql;
        END
    END
    ELSE IF @vers < @myVers
    BEGIN
        WHILE @vers < @myVers
        BEGIN
            SET @sql = N'EXEC undo_v' + CAST(@myVers AS NVARCHAR(10));
            EXEC sp_executesql @sql;
            SET @myVers = @myVers - 1;
        END
    END
END
GO
