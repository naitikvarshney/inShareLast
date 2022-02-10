require('dotenv').config();
const mongoose = require('mongoose');

function connectDB() {
    mongoose.connect(process.env.MONGO_CONNECTION_URL);
    const connection = mongoose.connection;

    connection.once('open', () => {
        console.log('Hurray! DataBase Connected.');
    }).on('error', function (err) {
        console.log('Failed!');
    });
}

module.exports = connectDB;
