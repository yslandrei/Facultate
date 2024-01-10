use ebay_db_manual
go

-- validators --

create or alter function validate_number
(
    @number varchar(50)
)
returns bit
as
begin
    if @number is null
        return 0
    if ltrim(@number) = ''
        return 0

    declare @len int
    set @len = len(@number)

    declare @index int
    set @index = 1

    declare @car char

    while @index < @len
    begin
        select @car = substring(@number, @index, 1)
        if isnumeric(@car) != 1
            return 0
        set @index = @index + 1
    end

    return 1
end
go

create or alter function validate_string
(
    @string varchar(50)
)
returns bit
as
begin
    if @string is null
        return 0
    if ltrim(@string) = ''
        return 0

    declare @len int
    set @len = len(@string)

    declare @index int
    set @index = 1

    while @index < @len
    begin
        if not substring(@string, @index, 1) like '%[.\-a-zA-Z@1-9\ ]'
            return 0

        set @index = @index + 1
    end

    return 1
end
go

create or alter function validate_date
(
    @date varchar(50)
)
returns bit
as
begin
    if @date is null
        return 0
    if ltrim(@date) = ''
        return 0

    declare @datetime datetime
    set @datetime = try_cast(@date as datetime);

    if @datetime is null
        return 0

    return 1
end
go

-- crud --

-- product --

create or alter procedure add_product
(
    @name varchar(50),
    @created_date varchar(50),
    @seller_id varchar(50),
    @category_id varchar(50),
    @price varchar(50)
)
as
begin
    declare @valid bit
    set @valid = 1

    if dbo.validate_string(@name) = 0
        set @valid = 0
    if dbo.validate_date(@created_date) = 0
        set @valid = 0
	if dbo.validate_number(@price) = 0
        set @valid = 0
	if dbo.validate_number(@seller_id) = 0
        set @valid = 0
	if dbo.validate_number(@category_id) = 0
        set @valid = 0

	if @valid = 0
	begin
		print 'invalid data'
		return
	end

	if not exists(select * from seller where seller.id = cast(@seller_id as bigint))
	begin
		print 'seller_id is not found in table seller'
		return
	end

	if not exists(select * from category where category.id = cast(@category_id as bigint))
	begin
		print 'category_id is not found in table category'
		return
	end

	insert into product 
	values (@name, cast(@created_date as datetime), cast(@seller_id as bigint), cast(@category_id as bigint), cast(@price as money))
	
	print 'product added succesfully'

end
go

create or alter procedure get_product
(
	@id varchar(50)
)
as
begin

	if dbo.validate_number(@id) = 0
	begin
		print 'Invalid Data'
		return
	end
	
	if not exists(select * from product where product.id = cast(@id as bigint))
	begin
		print 'id is not found in table product'
		return
	end

	select * from product where product.id = cast(@id as bigint)

	print 'product found succesfully'
		
end
go

create or alter procedure delete_product
(
	@id varchar(50)
)
as
begin
	if dbo.validate_number(@id) = 0
	begin
		print 'Invalid Data'
		return
	end
	
	if not exists(select * from product where product.id = cast(@id as bigint))
	begin
		print 'id is not found in table product'
		return
	end

	delete product where product.id = cast(@id as bigint)

	print 'product deleted succesfully'

end
go

create or alter procedure update_product
(
	@id varchar(50),
	@name varchar(50),
    @created_date varchar(50),
    @seller_id varchar(50),
    @category_id varchar(50),
    @price varchar(50)
)
as
begin
	declare @valid bit
    set @valid = 1

	if dbo.validate_number(@id) = 0
        set @valid = 0
    if dbo.validate_string(@name) = 0
        set @valid = 0
    if dbo.validate_date(@created_date) = 0
        set @valid = 0
	if dbo.validate_number(@price) = 0
        set @valid = 0
	if dbo.validate_number(@seller_id) = 0
        set @valid = 0
	if dbo.validate_number(@category_id) = 0
        set @valid = 0

	if @valid = 0
	begin
		print 'invalid data'
		return
	end
	
	if not exists(select * from product where product.id = cast(@id as bigint))
	begin
		print 'id is not found in table product'
		return
	end

	if not exists(select * from seller where seller.id = cast(@seller_id as bigint))
	begin
		print 'seller_id is not found in table seller'
		return
	end

	if not exists(select * from category where category.id = cast(@category_id as bigint))
	begin
		print 'category_id is not found in table category'
		return
	end

	update product set product.name = @name, created_date = cast(@created_date as datetime), seller_id = cast(@seller_id as bigint), category_id = cast(@category_id as bigint), price = cast(@price as bigint)
	where product.id = cast(@id as bigint)

	print 'product updated succesfully'

end
go

-- buyer --

create or alter procedure add_buyer
(
    @name varchar(50),
    @email varchar(50),
    @address_id varchar(50)
)
as
begin
    declare @valid bit
    set @valid = 1

    if dbo.validate_string(@name) = 0
        set @valid = 0
	if dbo.validate_string(@email) = 0
        set @valid = 0
	if dbo.validate_number(@address_id) = 0
        set @valid = 0

	if @valid = 0
	begin
		print 'invalid data'
		return
	end

	if not exists(select * from address where address.id = cast(@address_id as bigint))
	begin
		print 'address_id is not found in table address'
		return
	end

	insert into buyer 
	values (@name, @email, cast(@address_id as bigint))
	
	print 'buyer added succesfully'

end
go

create or alter procedure get_buyer
(
	@id varchar(50)
)
as
begin

	if dbo.validate_number(@id) = 0
	begin
		print 'Invalid Data'
		return
	end
	
	if not exists(select * from buyer where buyer.id = cast(@id as bigint))
	begin
		print 'id is not found in table buyer'
		return
	end

	select * from buyer where buyer.id = cast(@id as bigint)

	print 'buyer found succesfully'
		
end
go

create or alter procedure delete_buyer
(
	@id varchar(50)
)
as
begin
	if dbo.validate_number(@id) = 0
	begin
		print 'Invalid Data'
		return
	end
	
	if not exists(select * from buyer where buyer.id = cast(@id as bigint))
	begin
		print 'id is not found in table buyer'
		return
	end

	delete buyer where buyer.id = cast(@id as bigint)

	print 'buyer deleted succesfully'

end
go

create or alter procedure update_buyer
(
	@id varchar(50),
	@name varchar(50),
    @email varchar(50),
    @address_id varchar(50)
)
as
begin
	declare @valid bit
    set @valid = 1

	if dbo.validate_number(@id) = 0
		set @valid = 0
    if dbo.validate_string(@name) = 0
        set @valid = 0
	if dbo.validate_string(@email) = 0
        set @valid = 0
	if dbo.validate_number(@address_id) = 0
        set @valid = 0

	if @valid = 0
	begin
		print 'invalid data'
		return
	end
	
	if not exists(select * from buyer where buyer.id = cast(@id as bigint))
	begin
		print 'id is not found in table buyer'
		return
	end

	if not exists(select * from address where address.id = cast(@address_id as bigint))
	begin
		print 'address_id is not found in table address'
		return
	end

	update buyer set buyer.name = @name, email = @email, address_id = cast(@address_id as bigint)
	where buyer.id = cast(@id as bigint)

	print 'buyer updated succesfully'

end
go

-- sale --

create or alter procedure add_sale
(
    @buyer_id varchar(50),
    @product_id varchar(50),
    @transaction_date varchar(50),
    @transporter_id varchar(50)
)
as
begin
    declare @valid bit
    set @valid = 1

	if dbo.validate_number(@buyer_id) = 0
        set @valid = 0
	if dbo.validate_number(@product_id) = 0
        set @valid = 0
	if dbo.validate_date(@transaction_date) = 0
        set @valid = 0
	if dbo.validate_number(@transporter_id) = 0
        set @valid = 0

	if @valid = 0
	begin
		print 'invalid data'
		return
	end

	if not exists(select * from buyer where buyer.id = cast(@buyer_id as bigint))
	begin
		print 'buyer_id is not found in table buyer'
		return
	end

	if not exists(select * from product where product.id = cast(@product_id as bigint))
	begin
		print 'product_id is not found in table product'
		return
	end

	if not exists(select * from transporter where transporter.id = cast(@transporter_id as bigint))
	begin
		print 'transporter_id is not found in table transporter'
		return
	end

	insert into sale 
	values (cast(@buyer_id as bigint), cast(@product_id as bigint), cast(@transaction_date as datetime), cast(@transporter_id as bigint))
	
	print 'sale added succesfully'

end
go

create or alter procedure get_sale
(
	@buyer_id varchar(50),
    @product_id varchar(50),
    @transaction_date varchar(50)
)
as
begin

	declare @valid bit
    set @valid = 1

	if dbo.validate_number(@buyer_id) = 0
        set @valid = 0
	if dbo.validate_number(@product_id) = 0
        set @valid = 0
	if dbo.validate_date(@transaction_date) = 0

	if @valid = 0
	begin
		print 'invalid data'
		return
	end

	if not exists(select * from buyer where buyer.id = cast(@buyer_id as bigint))
	begin
		print 'buyer_id is not found in table buyer'
		return
	end

	if not exists(select * from product where product.id = cast(@product_id as bigint))
	begin
		print 'product_id is not found in table product'
		return
	end

	select * from sale
	where sale.buyer_id = cast(@buyer_id as bigint) and sale.product_id = cast(@product_id as bigint) and sale.transaction_date = cast(@transaction_date as datetime) 

	print 'sale found succesfully'
		
end
go

create or alter procedure delete_sale
(
	@buyer_id varchar(50),
    @product_id varchar(50),
    @transaction_date varchar(50)
)
as
begin
	declare @valid bit
    set @valid = 1

	if dbo.validate_number(@buyer_id) = 0
        set @valid = 0
	if dbo.validate_number(@product_id) = 0
        set @valid = 0
	if dbo.validate_date(@transaction_date) = 0

	if @valid = 0
	begin
		print 'invalid data'
		return
	end

	if not exists(select * from buyer where buyer.id = cast(@buyer_id as bigint))
	begin
		print 'buyer_id is not found in table buyer'
		return
	end

	if not exists(select * from product where product.id = cast(@product_id as bigint))
	begin
		print 'product_id is not found in table product'
		return
	end

	delete sale
	where sale.buyer_id = cast(@buyer_id as bigint) and sale.product_id = cast(@product_id as bigint) and sale.transaction_date = cast(@transaction_date as datetime) 

	print 'sale deleted succesfully'

end
go

create or alter procedure update_sale
(
	@buyer_id varchar(50),
    @product_id varchar(50),
    @transaction_date varchar(50),
    @transporter_id varchar(50)
)
as
begin
	declare @valid bit
    set @valid = 1

	if dbo.validate_number(@buyer_id) = 0
        set @valid = 0
	if dbo.validate_number(@product_id) = 0
        set @valid = 0
	if dbo.validate_date(@transaction_date) = 0
        set @valid = 0
	if dbo.validate_number(@transporter_id) = 0
        set @valid = 0

	if @valid = 0
	begin
		print 'invalid data'
		return
	end

	if not exists(select * from buyer where buyer.id = cast(@buyer_id as bigint))
	begin
		print 'buyer_id is not found in table buyer'
		return
	end

	if not exists(select * from product where product.id = cast(@product_id as bigint))
	begin
		print 'product_id is not found in table product'
		return
	end

	update sale set sale.transporter_id = @transporter_id
	where sale.buyer_id = cast(@buyer_id as bigint) and sale.product_id = cast(@product_id as bigint) and sale.transaction_date = cast(@transaction_date as datetime) 

	print 'sale updated succesfully'

end
go

-- VIEW --
create or alter view view_sales_and_products_after_2020 as
	select product.name, product.price, sale.transaction_date from sale
	join product on product.id = sale.product_id
	where YEAR(transaction_date) > 2020
go

if exists(select name from sys.indexes where name = 'index_sales_transaction_date')
    drop index index_sales_transaction_date on sale
go
create nonclustered index index_sales_transaction_date on sale(transaction_date)
go

create or alter view view_sales_and_buyers_and_products_cheaper_than_1000 as
	select buyer.name as buyer_name, buyer.email, product.name as product_name, product.price, sale.transaction_date from sale
	join buyer on buyer.id = sale.buyer_id
	join product on product.id = sale.product_id
	where price < 1000
go

if exists(select name from sys.indexes where name = 'index_product_price')
    drop index index_product_price on product
go
create nonclustered index index_product_price on product(price)
go

-- RUNS --

exec add_buyer 'George', 'george@gmail.com', '4'

exec get_buyer '10005'

exec update_buyer '10005', 'George Popescu', 'george@gmail.com', '4'

exec delete_buyer '10005'

exec add_product 'Placa Video', '2022-10-10 00:00:00.000', '6', '1', '2000'

exec get_product '21020'

exec update_product '21020', 'Placa Video', '2022-10-10 00:00:00.000', '6', '1', '2500'

exec delete_product '21020'

exec add_sale '10005', '21020', '2022-10-11 00:00:00.000', '2'

exec update_sale '10005', '21020', '2022-10-11 00:00:00.000', '3'

exec get_sale '10005', '21020', '2022-10-11 00:00:00.000'

exec delete_sale '10005', '21020', '2022-10-11 00:00:00.000'

select * from view_sales_and_buyers_and_products_cheaper_than_1000

select * from view_sales_and_products_after_2020

select * from buyer
select * from product
select * from sale



