def generate_tickets(n):
    options = ["1", "2", "X"]
    tickets = []
    for i in range(n):
        if i == n - 1:
            options.remove("X")
        if i == 0:
            tickets = options
        else:
            new_tickets = []
            for ticket in tickets:
                for option in options:
                    new_tickets.append(ticket + option)
            tickets = new_tickets
    return tickets

tickets = generate_tickets(5)
print(tickets)