#include "project.h"

project::project()
{

}
project::project(int id, const QString& title, const QString& desc, const QDate& startDate, const QDate& endDate)
    : Projectid(id), Ptitle(title), Pdesc(desc), StartDate(startDate), EndDate(endDate)
{

}

project::project(const project& other)
    : Projectid(other.Projectid), Ptitle(other.Ptitle), Pdesc(other.Pdesc),
      StartDate(other.StartDate), EndDate(other.EndDate)
{

}
