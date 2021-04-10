from django.db import models


# Create your models here.
from cyp.models import Department
from cyp.models import Designation


class Teacher(models.Model):
    name = models.CharField(max_length=100)
    departments = models.ManyToManyField(Department)
    designation = models.ForeignKey(Designation, on_delete=models.CASCADE)
    description = models.TextField(blank=True, null=True)
    created_at = models.DateTimeField(auto_now_add=True)
    modified_at = models.DateTimeField(auto_now=True)
    status = models.BooleanField(default=False)

    def __str__(self):
        return self.name
