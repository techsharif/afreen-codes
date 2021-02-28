SELECT DISTINCT `name`
  FROM `movies`
  JOIN `stars`
  	ON `movies`.`id` = `movie_id`
  JOIN `people`
  	ON `people`.`id` = `person_id`
  WHERE `year` = 2004
  ORDER BY `birth`;