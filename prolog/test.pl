hasRoom(Hotel,City,Type,Arrival,Departure,Price).
flight(Airline,FromCity,ToCity,Arrival,Departure,Price).
ticket(City,Date,Attraction,Price).

% Rooms available in hotels
hasRoom('Hilton', 'New York', 'double', 1223, 1229, 200).
hasRoom('Marriott', 'New York', 'double', 1223, 1229, 180).
hasRoom('Sheraton', 'New York', 'double', 1223, 1229, 220).
hasRoom('Holiday Inn', 'Toronto', 'single', 1223, 1229, 120).
hasRoom('Fairmont', 'Vancouver', 'suite', 1225, 1230, 350).

% Flights between cities
flight('Air Canada', 'Toronto', 'Addis Abeba', 1221, 1227, 1900).
flight('Ethiopian Airlines', 'Toronto', 'Addis Abeba', 1221, 1227, 2500).
flight('United Airlines', 'New York', 'Paris', 1215, 1222, 800).
flight('Delta Airlines', 'Toronto', 'New York', 1201, 1207, 350).

% Tickets to attractions
ticket('New York', 1227, 'Opera', 150).
ticket('New York', 1228, 'Metropolitan Museum of Art', 100).
ticket('New York', 1227, 'Broadway Show', 200).
ticket('Toronto', 1224, 'CN Tower', 50).
ticket('Vancouver', 1226, 'Capilano Suspension Bridge', 70).
