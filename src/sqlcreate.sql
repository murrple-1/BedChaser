INSERT INTO "regions" (`name`, `map_x_offset`, `map_y_offset`, `sub_map_file_path`) VALUES
	('Renfrew County', 150, 150, 'images/Renfrew_County.jpg'),
	('North Lanark/North Grenville', 275, 275, 'images/North_Lanark_North_Grenville.jpg'),
	('Ottawa West', 320, 200, 'images/Ottawa_West.jpg'),
	('Ottawa Center', 400, 220, 'images/Ottawa_Center.jpg'),
	('Ottawa East', 415, 180, 'images/Ottawa_East.jpg'),
	('Eastern Counties', 490, 225, 'images/Eastern_Counties.jpg');

INSERT INTO "facilities" (`name`, `map_x_offset`, `map_y_offset`, `number_of_acute_care_beds`, `number_of_complex_continuing_care_beds`, `number_of_long_term_care_beds`, `regions_id`) VALUES
	('FAC1', 15, 40, 3, 6, 22, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa East')),
	('FAC2', 41, 41, 13, 13, 14, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa Center')),
	('FAC3', 9, 17, 1, 15, 7, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa Center')),
	('FAC4', 11, 22, 14, 2, 20, (SELECT `id` FROM "regions" WHERE `name` = 'North Lanark/North Grenville')),
	('FAC5', 20, 19, 9, 7, 7, (SELECT `id` FROM "regions" WHERE `name` = 'Eastern Counties')),
	('FAC6', 20, 0, 4, 29, 17, (SELECT `id` FROM "regions" WHERE `name` = 'Eastern Counties')),
	('FAC7',22, 25, 13, 27, 23, (SELECT `id` FROM "regions" WHERE `name` = 'North Lanark/North Grenville')),
	('FAC8', 29, 35, 5, 16, 6, (SELECT `id` FROM "regions" WHERE `name` = 'Renfrew County')),
	('FAC9', 20, 26, 3, 2, 25, (SELECT `id` FROM "regions" WHERE `name` = 'Renfrew County')),
	('FAC10', 1, 10, 6, 15, 4, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa Center')),
	('FAC11', 1, 19, 4, 19, 12, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa East')),
	('FAC12', 29, 34, 1, 19, 0, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa East')),
	('FAC13', 45, 38, 15, 11, 11, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa West')),
	('FAC14', 1, 0, 15, 1, 12, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa Center')),
	('FAC15', 13, 5, 6, 29, 15, (SELECT `id` FROM "regions" WHERE `name` = 'Eastern Counties'));
