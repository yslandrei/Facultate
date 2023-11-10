USE [ebay_db_manual]
GO
INSERT [dbo].[category] ([name]) VALUES (N'PC & Related')
GO
INSERT [dbo].[category] ([name]) VALUES (N'Furniture')
GO
INSERT [dbo].[category] ([name]) VALUES (N'Electronics')
GO
INSERT [dbo].[address] ([country], [city], [street], [postal_code]) VALUES (N'Romania', N'Cluj-Napoca', N'Teodor Mihali nr 59', N'400111')
GO
INSERT [dbo].[address] ([country], [city], [street], [postal_code]) VALUES (N'Romania', N'Cluj-Napoca', N'Mihai Viteazu nr 11', N'400503')
GO
INSERT [dbo].[address] ([country], [city], [street], [postal_code]) VALUES (N'Romania', N'Ramnicu Valcea', N'Calea lui Traian nr 146', N'240011')
GO
INSERT [dbo].[address] ([country], [city], [street], [postal_code]) VALUES (N'Romania', N'Bucuresti', N'Magheru nr 14', N'010337')
GO
INSERT [dbo].[address] ([country], [city], [street], [postal_code]) VALUES (N'Romania', N'Ramnicu Valcea', N'Aleea Panselutelor', N'240242')
GO
INSERT [dbo].[address] ([country], [city], [street], [postal_code]) VALUES (N'Hungary', N'Budapest', N'János Bolyai', N'001212')
GO
INSERT [dbo].[address] ([country], [city], [street], [postal_code]) VALUES (N'Germany', N'Berlin', N'Dorfstrasse', N'701823')
GO
INSERT [dbo].[address] ([country], [city], [street], [postal_code]) VALUES (N'United Kingdom', N'Manchester', N'Saint Patrick', N'123123')
GO
INSERT [dbo].[address] ([country], [city], [street], [postal_code]) VALUES (N'Romania', N'Ploiesti', N'Victoriei', N'300120')
GO
INSERT [dbo].[seller] ([name], [address_id], [email]) VALUES (N'Marius Shop', 0, N'marius@gmail.com')
GO
INSERT [dbo].[seller] ([name], [address_id], [email]) VALUES (N'PC Components', 1, N'pccomponents@gmail.com')
GO
INSERT [dbo].[seller] ([name], [address_id], [email]) VALUES (N'Furniture Shop', 2, N'furnitureshop@gmail.com')
GO
INSERT [dbo].[seller] ([name], [address_id], [email]) VALUES (N'Electronics Shop', 2, N'electronicsshop@gmail.com')
GO
INSERT [dbo].[product] ([name], [created_date], [seller_id], [category_id], [price]) VALUES (N'Procesor i7', CAST(N'2020-10-10' AS Date), 6, 1, 1200.0000)
GO
INSERT [dbo].[product] ([name], [created_date], [seller_id], [category_id], [price]) VALUES (N'Canapea', CAST(N'2022-10-10' AS Date), 7, 2, 3000.0000)
GO
INSERT [dbo].[product] ([name], [created_date], [seller_id], [category_id], [price]) VALUES (N'Fotoliu', CAST(N'2023-11-11' AS Date), 7, 2, 1000.0000)
GO
INSERT [dbo].[product] ([name], [created_date], [seller_id], [category_id], [price]) VALUES (N'Prelungitor', CAST(N'2019-08-12' AS Date), 8, 3, 40.0000)
GO
INSERT [dbo].[buyer] ([name], [address_id], [email]) VALUES (N'Andrei Diaconescu', 4, N'andreidiaconescu@gmail.com')
GO
INSERT [dbo].[buyer] ([name], [address_id], [email]) VALUES (N'Teodor Domnica', 8, N'teodordomnica@gmail.com')
GO
INSERT [dbo].[buyer] ([name], [address_id], [email]) VALUES (N'Ivancu Andrei', 4, N'ivancuandrei@gmail.com')
GO
INSERT [dbo].[transporter] ([name], [price_per_km]) VALUES (N'Urgent Cargus', 0.1000)
GO
INSERT [dbo].[transporter] ([name], [price_per_km]) VALUES (N'Fan Courier', 0.0900)
GO
INSERT [dbo].[transporter] ([name], [price_per_km]) VALUES (N'Romanian Post Office', 0.0500)
GO
INSERT [dbo].[transporter] ([name], [price_per_km]) VALUES (N'DHL', 0.1200)
GO
INSERT [dbo].[sale] ([buyer_id], [product_id], [transaction_date], [transporter_id]) VALUES (4, 5, CAST(N'2023-10-08T12:00:00.000' AS DateTime), 2)
GO
INSERT [dbo].[sale] ([buyer_id], [product_id], [transaction_date], [transporter_id]) VALUES (5, 6, CAST(N'2023-10-07T16:00:00.000' AS DateTime), 1)
GO
INSERT [dbo].[sale] ([buyer_id], [product_id], [transaction_date], [transporter_id]) VALUES (6, 7, CAST(N'2023-09-10T07:00:00.000' AS DateTime), 3)
GO
INSERT [dbo].[employee] ([name], [salary], [hours_per_day], [address_id]) VALUES (N'Tudor Popescu', 4000.0000, 8, 1)
GO
INSERT [dbo].[employee] ([name], [salary], [hours_per_day], [address_id]) VALUES (N'Cristiana Ionescu', 8000.0000, 8, 2)
GO
INSERT [dbo].[employee] ([name], [salary], [hours_per_day], [address_id]) VALUES (N'George John', 4500.0000, 4, 3)
GO
INSERT [dbo].[employee] ([name], [salary], [hours_per_day], [address_id]) VALUES (N'Istvan Szekely', 6000.0000, 6, 5)
GO
INSERT [dbo].[employee] ([name], [salary], [hours_per_day], [address_id]) VALUES (N'Alina Manu', 10000.0000, 8, 7)
GO
INSERT [dbo].[department] ([name]) VALUES (N'Customer Service')
GO
INSERT [dbo].[department] ([name]) VALUES (N'Software Development')
GO
INSERT [dbo].[department] ([name]) VALUES (N'Management')
GO
INSERT [dbo].[employee_department] ([employee_id], [department_id], [starting_date]) VALUES (1, 1, CAST(N'2022-05-10' AS Date))
GO
INSERT [dbo].[employee_department] ([employee_id], [department_id], [starting_date]) VALUES (2, 2, CAST(N'2021-05-02' AS Date))
GO
INSERT [dbo].[employee_department] ([employee_id], [department_id], [starting_date]) VALUES (3, 2, CAST(N'2023-02-10' AS Date))
GO
INSERT [dbo].[employee_department] ([employee_id], [department_id], [starting_date]) VALUES (4, 2, CAST(N'2020-10-10' AS Date))
GO
INSERT [dbo].[employee_department] ([employee_id], [department_id], [starting_date]) VALUES (5, 2, CAST(N'2016-06-06' AS Date))
GO
INSERT [dbo].[employee_department] ([employee_id], [department_id], [starting_date]) VALUES (5, 3, CAST(N'2020-01-01' AS Date))
GO
