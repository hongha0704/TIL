class Player:
    def __init__(self, name, avg, hr):
        self.name = name
        self.avg = avg
        self.hr = hr

    def update_name(self, new_name):
        self.name = new_name

    def update_avg(self, new_avg):
        self.avg = new_avg
        
    def update_hr(self, new_hr):
        self.hr = new_hr