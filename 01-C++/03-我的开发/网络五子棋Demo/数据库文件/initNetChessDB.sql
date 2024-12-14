create database NetChessDB
on
(
	name=NetChessDB,
	filename='d:\NetChessDB.mdf',
	size=20,
	maxsize=unlimited,
	filegrowth=2%
)
log on
(
	name=NetChessLog,
	filename='d:\NetChessLog.ldf',
	size=5,
	maxsize=10,
	filegrowth=10%
)
go
use NetChessDB
go
create table Player
(
	PName varchar(20) primary key,
	PPwd varchar(20) not null,
	PIcon varchar(20),
	PLevel varchar(5),
	PSumCount varchar(20),
	PWinCount varchar(20),
	PPower varchar(20)
)
go
create table Friend
(
	PName varchar(20) foreign key references Player(PName),
	PFName varchar(20) foreign key references Player(PName),
)
go
create table FitInfo
(
	PName varchar(20) foreign key references Player(PName),
	Ftime char(20) not null,
	PCtrName varchar(20) foreign key references Player(PName),
	FResult char(2) not null,
	TTime char(10) not null,
)
go
select * from Player
select * from Friend
select * from FitInfo