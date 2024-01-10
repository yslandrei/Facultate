create view View_table as
	select buyer.id, buyer.name from buyer
go

create view View_tables as
	select buyer.id, buyer.name, sale.buyer_id, sale.transaction_date from sale
	join buyer on sale.buyer_id=buyer.id
go

create view View_tables_group_by as
	select product.name, count(*) as num_products from product
	join sale on sale.product_id=product.id
	group by product.name
go