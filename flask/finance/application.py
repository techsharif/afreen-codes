import os

import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

try:
    query = '''

    UPDATE users SET cash=?;

    '''
    # db.execute(query, 10000)

    query = '''

    DROP table history;

    '''
    # db.execute(query)

    query = '''
    create table history
    (
    	id integer
    		constraint history_pk
    			primary key autoincrement,
    	user_id integer,
    	symbol text,
    	name text,
    	shares integer,
    	price numeric,
    	transacted text
    );

    '''
    db.execute(query)
except Exception as e:
    print(e)


@app.route("/")
@login_required
def index():

    user_id = session["user_id"]

    query = "SELECT * FROM users WHERE id=?"
    user_data = db.execute(query, user_id)[0]

    cash = usd(float(user_data["cash"]))

    query = "SELECT symbol, name, sum(shares) s, price FROM history WHERE user_id=? GROUP BY symbol"
    history_data = db.execute(query, user_id)

    data = []
    total = float(user_data["cash"])
    for history in history_data:
        if history["s"]:
            total += history["price"] * history["s"]
            history["total"] = usd(history["price"] * history["s"])
            history["price"] = usd(history["price"])
            history["shares"] = history["s"]
            data += [history]

    total = usd(total)

    """Show portfolio of stocks"""
    return render_template("home.html", data=data, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        try:
            shares = int(shares)
        except:
            return apology("invalid shares", 400)

        if shares < 1:
            return apology("invalid shares", 400)

        if not symbol:
            return apology("invalid symbol", 400)

        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)

        user = session["user_id"]

        query = "SELECT * FROM users WHERE id=?"
        user_row = db.execute(query, user)[0]

        balance = float(user_row["cash"])

        if balance < stock["price"] * shares:
            return apology("can't afford", 400)

        query = "INSERT INTO history (user_id, symbol, name, shares, price, transacted) VALUES (?, ?, ?, ?, ?, ?);"
        db.execute(query, user, stock["symbol"], stock["name"], shares, stock["price"], str(datetime.datetime.now()))

        query = "update users SET cash = ? WHERE id = ?"
        db.execute(query, (balance - stock["price"] * shares), user)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("invalid symbol", 400)
        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)

        stock["price"] = usd(stock["price"])
        return render_template("quoted.html", stock=stock)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 400)

        if not request.form.get("confirmation"):
            return apology("must provide password (again)", 400)

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords are not same", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) == 1:
            return apology("User already exits", 400)

        # Query database for username
        query = "INSERT INTO users (username, hash) VALUES (?, ?)"
        row = db.execute(query, request.form.get("username"), generate_password_hash(request.form.get("password")))

        session["user_id"] = row
        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        try:
            shares = int(shares)
        except:
            return apology("invalid shares", 400)

        if shares < 1:
            return apology("invalid shares", 400)

        if not symbol:
            return apology("invalid symbol", 400)

        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)

        user = session["user_id"]

        query = "SELECT * FROM users WHERE id=?"
        user_row = db.execute(query, user)[0]

        balance = float(user_row["cash"])
        price = stock["price"] * shares

        query = "SELECT sum(shares) s FROM history WHERE user_id=? AND symbol=? GROUP BY symbol"
        history_data = db.execute(query, user, symbol)

        if not len(history_data):
            return apology("invalid symbol", 400)

        if history_data[0]["s"] < shares:
            return apology("insufficient shares", 400)

        new_balance = balance + price

        query = "INSERT INTO history (user_id, symbol, name, shares, price, transacted) VALUES (?, ?, ?, ?, ?, ?);"
        db.execute(query, user, stock["symbol"], stock["name"], -shares, stock["price"], str(datetime.datetime.now()))

        query = "update users SET cash = ? WHERE id = ?"
        db.execute(query, new_balance, user)

        return redirect("/")

    else:
        user_id = session["user_id"]

        query = "SELECT symbol, name, sum(shares) s, price FROM history WHERE user_id=? GROUP BY symbol"
        history_data = db.execute(query, user_id)

        data = []
        for history in history_data:
            if history["s"]:
                data += [history["symbol"]]

        return render_template("sell.html", data=data)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

