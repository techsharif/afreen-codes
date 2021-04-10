from django.contrib import admin

from django_summernote.admin import SummernoteModelAdmin
from .models import University, Faculty, Department, Teacher


class DescriptionFieldAdmin(SummernoteModelAdmin):
    summernote_fields = ('description',)


class DescriptionAddressFieldAdmin(SummernoteModelAdmin):
    summernote_fields = ('description', 'address',)


admin.site.register(University, DescriptionAddressFieldAdmin)
admin.site.register(Faculty, DescriptionFieldAdmin)
admin.site.register(Department, DescriptionFieldAdmin)
admin.site.register(Teacher, DescriptionFieldAdmin)
