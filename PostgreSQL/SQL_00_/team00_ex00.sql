create table IF NOT EXISTS city_tour
(point1 varchar not null ,
 point2 varchar not null ,
 cost numeric not null default 1);

insert into city_tour values ('a','b',10);
insert into city_tour values ('a','c',15);
insert into city_tour values ('a','d',20);
insert into city_tour values ('b','a',10);
insert into city_tour values ('b','c',35);
insert into city_tour values ('b','d',25);
insert into city_tour values ('c','a',15);
insert into city_tour values ('c','b',35);
insert into city_tour values ('c','d',30);
insert into city_tour values ('d','a',20);
insert into city_tour values ('d','b',25);
insert into city_tour values ('d','c',30);

CREATE VIEW v_travel_way AS (WITH RECURSIVE travel (tour, last_city_name, total_cost, places_count) AS (
	SELECT
    	point1, point1, CAST(0 as numeric), 1
  	FROM city_tour 
  	WHERE point1 = 'a'

  	UNION ALL

  	SELECT
    	travel.tour || ',' || city_tour.point1,
		point1,
    	travel.total_cost + city_tour.cost,
    	travel.places_count + 1
  	FROM travel
	JOIN city_tour
	 	ON travel.last_city_name = city_tour.point2 AND 
		(position(city_tour.point1 IN travel.tour) = 0 OR 
		position(city_tour.point1 IN travel.tour) = 1)
)
	
SELECT DISTINCT total_cost, tour
	FROM travel
	WHERE places_count = 5 AND last_city_name = 'a' AND
	(position('b' IN travel.tour) != 0 AND
	position('c' IN travel.tour) != 0 AND 
	position('d' IN travel.tour) != 0));

SELECT total_cost, '{' || tour || '}' as tour
	FROM v_travel_way
WHERE total_cost = (SELECT MIN(total_cost) FROM v_travel_way)
ORDER BY total_cost, tour
