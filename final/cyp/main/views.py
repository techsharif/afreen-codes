from django.shortcuts import render
from django.views import View


class Test(View):
    template_name = 'test.html'

    def get(self, request):
        return render(request, self.template_name)