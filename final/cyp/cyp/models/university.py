from django.db import models


# Create your models here.

class University(models.Model):
    name = models.CharField(max_length=100)
    short_name = models.CharField(max_length=10, blank=True, null=True)
    address = models.TextField(blank=True, null=True)
    description = models.TextField(blank=True, null=True)
    created_at = models.DateTimeField(auto_now_add=True)
    modified_at = models.DateTimeField(auto_now=True)
    status = models.BooleanField(default=False)

    def __str__(self):
        return ("[" + self.short_name + "] ") if self.short_name else ' ' + self.name