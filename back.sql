create index xx on xxx(x);
select a,b,c from d where a > 100 and b < "200" and d>5.1;
delete from a where a>1 and d < 5.1;
insert into xx values(1,"50",5.1);
create table iloveyou (d int,e float,f char(8));
create table ifuckyou (g int,h float,i char(8));
create table ifdddyou (g int UNIQUE,h float,i char(8),PRIMARY KEY(i)); 
insert into iloveyou values(1,1.2,"12345678");
select d,e,f from iloveyou where d >1 and e < 5.1;